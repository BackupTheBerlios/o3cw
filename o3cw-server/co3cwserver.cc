#include "co3cwserver.h"
#include "cmysql.h"

o3cwapp::CO3CWServer::CO3CWServer(): o3cw::CO3CWBase::CO3CWBase(), users("user"), docs("doc")
{
    CO3CWBase::server=this;
    cmdexec=0;
    mysql=0;
    connections_handler=0;
    threads_num=1;
    admin_name="admin";
    
}

o3cwapp::CO3CWServer::~CO3CWServer()
{
}

int o3cwapp::CO3CWServer::Shutdown()
{
    if (connections_handler!=0)
        delete connections_handler;
    
    if (cmdexec!=0)
        delete [] cmdexec;
    
    if (mysql!=0)
        delete [] mysql;
    
    /* Shutdown MYSQL */
    o3cwapp::CMySQL::DeInit();
    
    /* Network cleanup */
    o3cw::CNetwork::Cleanup();
    
    return 0;
}

int o3cwapp::CO3CWServer::Run()
{
    const o3cw::CConfig &main_conf=o3cw::CO3CWBase::GetMainConfig();
    
    /* Global MYSQL initialisation */
    o3cwapp::CMySQL::Init();
    
    std::vector<std::string> request_results;
    
    main_conf.GetValue(threads_num,"limit","threads:workers");

    /* Creating connection to MySQL */
    mysql=new o3cwapp::CMySQL [threads_num];
    
    /* Default values */
    std::string host("localhost");
    std::string db("o3cw");
    std::string user("o3cw");
    std::string password("1234");
    
    /* Connecting */
    for (int i=0; i<threads_num; i++)
        mysql[i].Connect(main_conf.ReturnValue(host,"host","db"), main_conf.ReturnValue(db,"db_name","db"), main_conf.ReturnValue(user,"user","db"), main_conf.ReturnValue(password,"password","db"));
    
    /* host, db, user and password variables could be changed now! */

    connections_handler=new o3cw::CConnectionHandler;
    cmdexec=new o3cw::CCmdExec [threads_num];
    
    for (int i=0; i<threads_num; i++)
        cmdexec[i].Run(mysql[i]);
    return 0;
}

int o3cwapp::CO3CWServer::LoadConfig(const char *config_filename)
{
    /* Load main config */
    config.ParseFile(config_filename);
    o3cw::CO3CWBase::SetMainConfig(config);
    
    /* Example of config usage */   
    int val;
    const o3cw::CConfig *main_conf=&(o3cw::CO3CWBase::GetMainConfig());
    
    main_conf->GetValue(val,"default","net:timeout");
    printf("default net timeout is %i\n", val);
    
    main_conf->GetValue(val,"authorized","net:timeout");
    printf("net timeout for authorized users is %i\n", val);
    o3cw::CO3CWBase::GetMainConfig().GetValue(admin_name, "name", "authorization:admin");
    return 0;
}

int o3cwapp::CO3CWServer::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out)
{
    std::string c;
    if (cmd.CmdAviable())
    {
	std::string &c1=cmd.Pop();
        cmd_out.Push(c1);
        if (c1=="server")
        {
            /* This is exactly for me... */
	    if (cmd.CmdAviable())
            {
		std::string &c2=cmd.Pop();
                if (c2=="exit")
                {
                    if (cmd.GetClient().GetUser()!=0)
                    {
                        std::string username;
                        cmd.GetClient().GetUser()->GetName(username);
                        
                        if (cmd.GetClient().Trusted() && username==admin_name)
                        {
                            cmd_out.Push("exit");
                            cmd_out.Push("bye-bye!!");
                            printf(" * Normal shutdown\n");
                            for (int i=0; i<threads_num; i++)
                                cmdexec->Kill();
                            o3cw::CNetwork::cmd_bus.Destroy();
                            if (connections_handler!=0)
                                connections_handler->Kill();
                        }
                        else
                        {
                            return O3CW_ERR_DENIED;
                        }
                    }
                    else
                    {
                        return O3CW_ERR_DENIED;
                    }
                }
            }
            else
                return O3CW_ERR_BAD_SEQ;
        }
        else if (c1=="doc")
        {
            return docs.ExecCommand(cmd, cmd_out);
        }
        else if (c1=="user")
        {
            users.ExecCommand(cmd, cmd_out);
        }
        else
	{
            cmd_out.Push("error");
	    cmd_out.Push("not found");
	}
    }
    else
        return O3CW_ERR_BAD_SEQ;
    return 0;
}


