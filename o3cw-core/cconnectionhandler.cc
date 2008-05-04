#include "cconnectionhandler.h"
#include "cconfig.h"
#include "ccommand.h"
#include "error.h"

bonbon::CMutex o3cw::CConnectionHandler::connections_lock;
o3cw::CClient *o3cw::CConnectionHandler::listener=NULL;

o3cw::CConnectionHandler::CConnectionHandler(): o3cw::CNetwork::CNetwork()
{
    max_fd=-1;
    Run();
}

o3cw::CConnectionHandler::~CConnectionHandler()
{
   Join();
}

int o3cw::CConnectionHandler::ThreadExecute()
{
    o3cw::CConnectionHandler::connections_lock.Lock();
    
    const o3cw::CConfig *main_conf=&(o3cw::CO3CWBase::GetMainConfig());
    int port=25003;
    int timeout_unauth=20;
    int timeout_auth=120;
    int timeout=timeout_unauth;
    std::string net_interface("127.0.0.1");
    main_conf->GetValue(port,"port","net:server");
    main_conf->GetValue(net_interface,"interface","net:server");
   
    /* If listener doesnt' exist - create it. */
   
    if (o3cw::CConnectionHandler::listener==NULL)
    {
        o3cw::CClient *socklistner=new o3cw::CClient();
        if (socklistner==NULL)
            return O3CW_ERR_OUT_OF_MEM;
        printf(" * Turning on server at port %i on %s...", port, net_interface.c_str());
        if (socklistner->Bind(port,net_interface.c_str())+socklistner->Listen()==0)
            printf("OK\n");
        else
            printf("FAILED\n");
        
        socklistner->Listen();
        connections_store.push_back(socklistner);
        o3cw::CConnectionHandler::listener=socklistner;
        max_fd=o3cw::CClient::FdSetCompile(socket_set, connections_store);
    }
       

    o3cw::CConnectionHandler::connections_lock.UnLock();

    while (Killed()!=true)
    {
        std::queue<std::vector <o3cw::CClient *>::iterator> active_sock_list;
        
        /* Reading some settings at each cycle */
        main_conf->GetValue(timeout_unauth,"default","net:timeout");
        main_conf->GetValue(timeout_auth,"authorized","net:timeout");
        
        /* select sockets that changed */
        o3cw::CClient::readmultiselect(socket_set, max_fd, connections_store, active_sock_list, 1, 0);
        
        std::vector <o3cw::CClient *>::iterator timeout_it;
        for (timeout_it=connections_store.begin(); timeout_it!=connections_store.end(); timeout_it++)
        {
            o3cw::CClient *client=*timeout_it;
            
            if (client->Trusted())
                timeout=timeout_auth;
            else
                timeout=timeout_unauth;
            
            if (client->ConnectionTimeout()>timeout && client!=o3cw::CConnectionHandler::listener && client!=o3cw::CConnectionHandler::listener)
            {
                o3cw::CClient::FdSetRemove(socket_set, max_fd, connections_store, *client);
                client->ForceDown();
                to_delete.push(client);
                //delete client;
                connections_store.erase(timeout_it);
            }
        }
        
        while (active_sock_list.size()>0)
        {
            std::vector <o3cw::CClient *>::iterator active_sock_it=active_sock_list.front();
            active_sock_list.pop();
            o3cw::CClient *client=*active_sock_it;
            if (client!=NULL)
            {
                if (client==o3cw::CConnectionHandler::listener)
                {
                    /* New connection accepted */
                    printf(" * New client connected\n");
                    int t=client->Accept();
                    if (t>-1)
                    {
                        o3cw::CClient *new_client=new o3cw::CClient(t);
                        if (new_client==NULL)
                            return O3CW_ERR_OUT_OF_MEM;
                        connections_store.push_back(new_client);
                        o3cw::CClient::FdSetAdd(socket_set, max_fd, connections_store, *new_client);
                    }
                    else
                    {
                        /* Something wrong with listener? */
                    }
                }
                else
                {
                    /* New data from client */
                    printf(" * Got new data from client\n");
                    std::string message;
                    int r=client->Receive();
                    if (r==1)
                    {
                        /* New, full mesage received */
                        std::string *head=NULL;
                        std::string *body=NULL;
                        bool msg_left=((head=client->GetHead())!=NULL && ((body=client->GetBody())!=NULL));

                        while (msg_left)
                        {
                            /* Parse head and body, push new command to queue */
                            o3cw::CCommand *ptr_to_cmd=new o3cw::CCommand(*client, head, body);
                            if (ptr_to_cmd==NULL)
                                return O3CW_ERR_OUT_OF_MEM;
                            
                            cmd_bus.PushJob(ptr_to_cmd);
                            
			    msg_left=((head=client->GetHead())!=NULL && ((body=client->GetBody())!=NULL));
                        }
                        
                        /* Push back to connections_store */
                        //connections_store.push(client);
                        
                    }
                    else if (r==0)
                    {
                        /* Get something, but not a full message - just wait a bit more */
                        //connections_store.push(client);
                        
                    }
                    else
                    {
                        /* Connection lost */
                        printf(" * Connection lost.\n");
                        o3cw::CClient::FdSetRemove(socket_set, max_fd, connections_store, *client);
                        client->ForceDown();
                        //delete client;
                        to_delete.push(client);
                        connections_store.erase(active_sock_it);
                    }
                }
            }
        }
        
        int to_delete_size=to_delete.size();
        for (int i=0; i<to_delete_size; i++)
        {
            o3cw::CClient *client=to_delete.front();
            to_delete.pop();
            
            if (client->GetUseCount()==0)
            {
                printf("* ConnectionHandler: client deleted\n");
                delete client;
                to_delete_size--;
            }
            else
                to_delete.push(client);
        }
        
    }
    
    for (std::vector <o3cw::CClient *>::iterator it=connections_store.begin(); it!=connections_store.end(); it++)
    {
        delete *it;
    }
    return 0;
}
