#include "cconnectionhandler.h"

bonbon::CMutex o3cw::CConnectionHandler::connections_lock;
o3cw::CSocket *o3cw::CConnectionHandler::listener=NULL;

o3cw::CConnectionHandler::CConnectionHandler()
{
    printf("CONSTR\n");
    killed=false;
}

o3cw::CConnectionHandler::~CConnectionHandler()
{
   
}

void o3cw::CConnectionHandler::Kill()
{
    kill_lock.Lock();
    killed=true;
    kill_lock.UnLock();
}

bool o3cw::CConnectionHandler::Killed()
{
    bool result=false;
    kill_lock.Lock();
    if (killed)
        result=true;
    kill_lock.UnLock();
    return result;
}

int o3cw::CConnectionHandler::Execute()
{
    printf("Executing!\n");
    o3cw::CConnectionHandler::connections_lock.Lock();
    printf("lock p =[%p]\n", &o3cw::CConnectionHandler::connections_lock);
   
    /* If listener doesnt' exist - create it. */
   
    if (o3cw::CConnectionHandler::listener==NULL)
    {
        o3cw::CSocket *socklistner=new o3cw::CSocket();
        printf("Bind returns %i\n",socklistner->Bind(25003,"127.0.0.1"));
        printf("Listen returns %i\n",socklistner->Listen());
        connections_store.push(socklistner);
        o3cw::CConnectionHandler::listener=socklistner;
    }
       

    o3cw::CConnectionHandler::connections_lock.UnLock();

    while (Killed()!=true)
    {
        //printf("we are here!!!!!!!!!!!\n");

            printf("connection number=%i\n", connections_store.size());
        std::queue<o3cw::CSocket *> active_sock_list;
        o3cw::CSocket::readmultiselect(connections_store, active_sock_list, 1, 0);
        if (active_sock_list.size()!=0)
            printf("Something happened\n");
        std::vector<o3cw::CSocket *>::iterator active_sock;

        //for (active_sock=active_sock_list.begin(); active_sock!=active_sock_list.end(); active_sock++)
        while(active_sock_list.size()>0)
        {
            o3cw::CSocket *sock=active_sock_list.front();
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
                        o3cw::CSocket *new_client=new o3cw::CSocket(t);
                        new_client->Send("O3CW server greets you!\n");
                        connections_store.push(new_client);
                    }
                    else
                    {
                        printf("No one to accept\n");
                        /* Something wrong with listener? */
                    }
                    connections_store.push(sock);
                }
                else
                {
                    /* New data from client */
                    std::string message;
                    int r=sock->Receive(message, 1024);
                    if (r>-1)
                    {
                        printf("received [%s]\n", message.c_str());
                        if (message.length()>2)
                            sock->Send(message);
                        else
                        {
                                sock->Send("bye-bye.\n");
                                Kill();
                        }
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
