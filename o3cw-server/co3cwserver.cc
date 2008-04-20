#include "co3cwserver.h"
#include "co3cwbase.h"
#include "cconnectionhandler.h"
#include "cconfig.h"
#include "ccmdexec.h"

o3cw::CO3CWServer::CO3CWServer()
{

}

o3cw::CO3CWServer::~CO3CWServer()
{
    
}

int o3cw::CO3CWServer::Run()
{
    //Run connections handler (echo-server)
    o3cw::CConnectionHandler connections_handler;
    
    //Run 3 commands executors
    o3cw::CCmdExec cmdexec1;
    o3cw::CCmdExec cmdexec2;
    o3cw::CCmdExec cmdexec3;
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
