#include "co3cwserver.h"
#include "cmysql.h"

o3cwapp::CO3CWServer::CO3CWServer(): o3cw::CO3CWBase::CO3CWBase()
{
    CO3CWBase::server=this;

    connections_handler=NULL;
}

o3cwapp::CO3CWServer::~CO3CWServer()
{
    if (connections_handler!=NULL)
        delete connections_handler;
}

int o3cwapp::CO3CWServer::Run()
{
    const o3cw::CConfig &main_conf=o3cw::CO3CWBase::GetMainConfig();
    
    /* Global MYSQL initialisation */
    o3cwapp::CMySQL::Init();
    
    std::vector<std::string> request_results;
    
    /* Creating connection to MySQL */
    o3cwapp::CMySQL mysql;
    mysql.ThreadStart();
    
    /* Default values */
    std::string host("localhost");
    std::string db("o3cw");
    std::string user("o3cw");
    std::string password("1234");
    
    /* Connecting */
    mysql.Connect(main_conf.ReturnValue(host,"host","db"), main_conf.ReturnValue(db,"db_name","db"), main_conf.ReturnValue(user,"user","db"), main_conf.ReturnValue(password,"password","db"));
    
    /* host, db, user and password variables could be changed now! */
    
    /* Request DB */
    mysql.SQLRequest("select id, name, public_key from user");
    
    /* Getting all values */
    while (0==mysql.GetNextDataSet(request_results))
        printf("id=[%s] user=[%s] key=[%s]\n", request_results[0].c_str(), request_results[1].c_str(), request_results[2].c_str());
    
    /* Shutdowqn connection */
    mysql.ThreadEnd();
    
    /* Shutdown MYSQL */
    o3cwapp::CMySQL::DeInit();
    
    connections_handler=new o3cw::CConnectionHandler();
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
}

int o3cwapp::CO3CWServer::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out)
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
