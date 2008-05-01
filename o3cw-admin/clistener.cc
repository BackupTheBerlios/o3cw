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
        int t=client->Receive(0.01);
        if (0<t)
        {
            std::string *head=NULL;
            std::string *body=NULL;
	    bool msg_left=((head=client->GetHead())!=NULL && ((body=client->GetBody())!=NULL));

            while (msg_left)
            {
                /* Parse head and body, push new command to queue */
                o3cw::CCommand cmd=o3cw::CCommand(*client, head, body);
                cmd.Parse();
                std::string c;
                std::cout <<"\r";
                std::cout.flush();
                while (cmd.CmdAviable())
                {
		    std::string &c=cmd.Pop();
                    std::cout << c << std::endl;
                }
		std::cout << " * End of output" << std::endl << ">";
                std::cout.flush();
		cmd.FreeCryptedData();
		msg_left=((head=client->GetHead())!=NULL && ((body=client->GetBody())!=NULL));
            }
        }
        else if (t<0)
        {
            /* Connection lost? */
            Kill();
        }
    }
}
