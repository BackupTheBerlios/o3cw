#include "co3cwserver.h"

o3cw::CO3CWServer::CO3CWServer(): o3cw::CO3CWBase::CO3CWBase()
{
    CO3CWBase::server=this;
    //Initialize BonBon - little threads library.
    bonbon::BonbonInit();
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

int o3cw::CO3CWServer::ExecCommand(o3cw::CCommand &cmd)
{
    if (cmd.cmds.size()>0)
    {
        std::string *c=cmd.cmds.front();
        cmd.cmds.pop();
        if (c!=NULL)
        {
            std::string &destination=*c;
            if (destination=="server")
            {
                delete c;
                /* This is exactly for me... */
                if (cmd.cmds.size()>0)
                {
                    c=cmd.cmds.front();
                    cmd.cmds.pop();
                    if (c!=NULL)
                    {
                        std::string &command=*c;
                        if (command=="exit")
                        {
                            printf(" * Normal shutdown\n");
                            cmdexec1.Kill();
                            cmdexec2.Kill();
                            cmdexec3.Kill();
                            o3cw::CNetwork::cmd_bus.Destroy();
                            if (connections_handler!=NULL)
                                connections_handler->Kill();
                        }
                        delete c;
                    }
                }
                else
                    return -1;
            }
            //printf("cmd=[%s] len=%u\n", command.c_str(), command.length());
        }
    }
    else
        return -1;
    return 0;
}
