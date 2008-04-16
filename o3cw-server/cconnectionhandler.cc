#include "cconnectionhandler.h"

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
    printf("Executing!\n");
    o3cw::CConnectionHandler::connections_lock.Lock();
    printf("lock p =[%p]\n", &o3cw::CConnectionHandler::connections_lock);
   
    /* If listener doesnt' exist - create it. */
   
    if (o3cw::CConnectionHandler::listener==NULL)
    {
        o3cw::CClient *socklistner=new o3cw::CClient();
        printf("Creating listner by ME (%p)", this);
        printf("Bind returns %i\n",socklistner->Bind(25003,"127.0.0.1"));
        printf("Listen returns %i\n",socklistner->Listen());
        connections_store.push(socklistner);
        o3cw::CConnectionHandler::listener=socklistner;
    }
       

    o3cw::CConnectionHandler::connections_lock.UnLock();

    while (Killed()!=true)
    {
        //printf("we are here!!!!!!!!!!!\n");

            //printf("connection number=%i\n", connections_store.size());
        std::queue<o3cw::CClient *> active_sock_list;
        o3cw::CClient::readmultiselect(connections_store, active_sock_list, 1, 0);
        if (active_sock_list.size()!=0)
            printf("Something happened\n");

        //for (active_sock=active_sock_list.begin(); active_sock!=active_sock_list.end(); active_sock++)
        for (size_t i=0; i<connections_store.size(); i++)
        {
            o3cw::CClient *sock=connections_store.front();
            connections_store.pop();
            if (sock->ConnectionTimeout()>10)
            {
                sock->ForceDown();
                delete sock;
            }
            else
            {
                connections_store.push(sock);
            }
        }
        
        while(active_sock_list.size()>0)
        {
            o3cw::CClient *sock=active_sock_list.front();
            active_sock_list.pop();

            if (sock!=NULL)
            {
                printf("we got a sock\n");
                if (sock==o3cw::CConnectionHandler::listener)
                {
                    /* New connection accepted */
                    printf("Acceptor detected\n");
                    int t=sock->Accept();
                    if (t>-1)
                    {
                        o3cw::CClient *new_client=new o3cw::CClient(t);
                        new_client->Send("O3CW server greets you!\n");
                        connections_store.push(new_client);
                    }
                    else
                    {
                        printf("No one to accept\n");
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
                        msg_left=sock->GetHead(head)*sock->GetBody(head);

                        while (msg_left>0)
                        {
                            printf("New message received! head=[%s] body=[%s]\n", head.c_str(), body.c_str());
                            
                            /* Parse head and body, push new command to queue */
                            /* ... */
                            
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
                        printf("Connection lost.\n");
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
