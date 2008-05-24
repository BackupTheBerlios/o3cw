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
        int t=client->Receive(0.1);
        if (0<t)
        {
            std::string *head=0;
            std::string *body=0;
	    bool msg_left=((head=client->GetHead())!=0 && ((body=client->GetBody())!=0));

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
		msg_left=((head=client->GetHead())!=0 && ((body=client->GetBody())!=0));
            }
        }
        else if (t<0)
        {
            /* Connection lost? */
            Kill();
        }
    }
    return 0;
}
