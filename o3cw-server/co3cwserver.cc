#include "co3cwserver.h"

o3cw::CO3CWServer::CO3CWServer(): o3cw::CO3CWBase::CO3CWBase()
{
    CO3CWBase::server=this;

    connections_handler=NULL;
}

o3cw::CO3CWServer::~CO3CWServer()
{
    if (connections_handler!=NULL)
        delete connections_handler;
}

int o3cw::CO3CWServer::Run()
{
    connections_handler=new o3cw::CConnectionHandler();
}

int o3cw::CO3CWServer::LoadConfig(const char *config)
{
    /* Load main config */
    o3cw::CO3CWBase::LoadMainConfig(config);
    
    /* Example of config usage */   
    int val;
    const o3cw::CConfig *main_conf=&(o3cw::CO3CWBase::GetMainConfig());
    
    main_conf->GetValue(val,"default","net:timeout");
    printf("default net timeout is %i\n", val);
    
    main_conf->GetValue(val,"authorized","net:timeout");
    printf("net timeout for authorized users is %i\n", val);
}

int o3cw::CO3CWServer::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out)
{
    std::string c;
    if (cmd.CmdAviable())
    {
	std::string &c1=cmd.Pop();
        if (c1=="server")
        {
            cmd_out.Push("server");
            /* This is exactly for me... */
	    if (cmd.CmdAviable())
            {
		std::string &c2=cmd.Pop();
                if (c2=="exit")
                {
                    cmd_out.Push("exit");
                    cmd_out.Push("bye-bye!!");
                    printf(" * Normal shutdown\n");
                    cmdexec1.Kill();
                    cmdexec2.Kill();
                    cmdexec3.Kill();
                    o3cw::CNetwork::cmd_bus.Destroy();
                    if (connections_handler!=NULL)
                        connections_handler->Kill();
                }
            }
        }
        else if (c1=="doc")
        {
            cmd_out.Push("doc");
            return store.ExecCommand(cmd, cmd_out);
        }
        else
	{
            cmd_out.Push("error");
	    cmd_out.Push("not found");
	}
    }
    else
        return -1;
    return 0;
}
