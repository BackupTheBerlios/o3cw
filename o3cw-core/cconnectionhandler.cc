#include "cconnectionhandler.h"
#include "cconfig.h"
#include "ccommand.h"
#include "error.h"

bonbon::CMutex o3cw::CConnectionHandler::connections_lock;
o3cw::CClient *o3cw::CConnectionHandler::listener=NULL;

o3cw::CConnectionHandler::CConnectionHandler(): o3cw::CNetwork::CNetwork()
{
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
        connections_store.push(socklistner);
        o3cw::CConnectionHandler::listener=socklistner;
    }
       

    o3cw::CConnectionHandler::connections_lock.UnLock();

    while (Killed()!=true)
    {
        /* Reading some settings at each cycle */
        main_conf->GetValue(timeout_unauth,"default","net:timeout");
        main_conf->GetValue(timeout_auth,"authorized","net:timeout");
        
            //printf("connection number=%i\n", connections_store.size());
        std::queue<o3cw::CClient *> active_sock_list;
        o3cw::CClient::readmultiselect(connections_store, active_sock_list, 1, 0);

        //for (active_sock=active_sock_list.begin(); active_sock!=active_sock_list.end(); active_sock++)
        for (size_t i=0; i<connections_store.size(); i++)
        {
            o3cw::CClient *sock=connections_store.front();
            connections_store.pop();
            
            if (sock->Trusted())
                timeout=timeout_auth;
            else
                timeout=timeout_unauth;
            
            if (sock->ConnectionTimeout()>timeout && sock!=o3cw::CConnectionHandler::listener)
            {
                sock->ForceDown();
                delete sock;
            }
            else
                connections_store.push(sock);

        }
        
        while(active_sock_list.size()>0)
        {
            o3cw::CClient *sock=active_sock_list.front();
            active_sock_list.pop();

            if (sock!=NULL)
            {
                if (sock==o3cw::CConnectionHandler::listener)
                {
                    /* New connection accepted */
                    printf(" * New client connected\n");
                    int t=sock->Accept();
                    if (t>-1)
                    {
                        o3cw::CClient *new_client=new o3cw::CClient(t);
                        if (new_client==NULL)
                            return O3CW_ERR_OUT_OF_MEM;
                        new_client->Send("O3CW server greets you!\n");
                        connections_store.push(new_client);
                    }
                    else
                    {
                        /* Something wrong with listener? */
                    }
                    //printf("pushing...\n");
                    connections_store.push(sock);
                    //printf("pushed!\n");
                }
                else
                {
                    /* New data from client */
                    std::string message;
                    int r=sock->Receive();
                    if (r==1)
                    {
                        /* New, full mesage received */
                        int msg_left=1;
                        std::string head;
                        std::string body;
                        msg_left=sock->GetHead(head)*sock->GetBody(body);

                        while (msg_left>0)
                        {
                            /* Parse head and body, push new command to queue */
                            o3cw::CCommand *ptr_to_cmd=new o3cw::CCommand(*sock, body);
                            if (ptr_to_cmd==NULL)
                                return O3CW_ERR_OUT_OF_MEM;
                            cmd_bus.PushJob(ptr_to_cmd);
                            
                            msg_left=sock->GetHead(head)*sock->GetBody(head);
                        }
                        
                        /* Push back to connections_store */
                        connections_store.push(sock);
                        
                    }
                    else if (r==0)
                    {
                        /* Get something, but not a full message - just wait a bit more */
                        connections_store.push(sock);
                        
                    }
                    else
                    {
                        /* Connection lost */
                        printf(" * Connection lost.\n");
                        sock->ForceDown();
                        delete sock;
                    }
                }
            }
        }
    }
    
    while (connections_store.size()>0)
    {
        delete connections_store.front();
        connections_store.pop();
    }
    return 0;
}
