#include "clistener.h"
#include <iostream>

adm::CListener::CListener(o3cw::CClient *cl)
{
    client=cl;
    Run();
}

adm::CListener::~CListener()
{
    Join();
}

int adm::CListener::ThreadExecute()
{
    while (Killed()!=true)
    {
        if (0<client->Receive(0.01))
        {
            int msg_left=1;
            std::string head;
            std::string body;
            msg_left=client->GetHead(head)*client->GetBody(body);

            while (msg_left>0)
            {
                /* Parse head and body, push new command to queue */
                o3cw::CCommand cmd=o3cw::CCommand(*client, body);
                cmd.Parse();
                std::string c;
                std::cout <<"\r";
                std::cout.flush();
                while (cmd.Pop(c)==0)
                {
                    std::cout << " @ " << c << std::endl;
                }
                std::cout << ">";
                std::cout.flush();
                msg_left=client->GetHead(head)*client->GetBody(head);
            }
        }

    }
}
