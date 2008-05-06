#include "co3cwbase.h"
#include "cconfig.h"
#include "ccommand.h"
#include "cclient.h"

o3cw::CConfig *o3cw::CO3CWBase::o3cw_main_config=NULL;
o3cw::CO3CWBase *o3cw::CO3CWBase::server=NULL;
        
o3cw::CO3CWBase::CO3CWBase(): o3cw::CInTimeObject::CInTimeObject()
{

}

o3cw::CO3CWBase::~CO3CWBase()
{
    
}

int o3cw::CO3CWBase::SetMainConfig(o3cw::CConfig &config)
{
    int result=0;
//    mlock.Lock();
    o3cw_main_config=&config;
//    mlock.UnLock();
    return result;
}

int o3cw::CO3CWBase::ReLoadMainConfig(const char *filename)
{
    return o3cw_main_config->ParseFile(filename);
}

const o3cw::CConfig &o3cw::CO3CWBase::GetMainConfig()
{
    return *o3cw_main_config;
}

int o3cw::CO3CWBase::PushCommand(o3cw::CCommand &cmd)
{
    o3cw::CCommand results(cmd.GetClient());
    /* Parse command and push it further */

    int result=o3cw::CO3CWBase::server->ExecCommand(cmd, results);
    
    /* Remove all commands left */
    //while (cmd.Pop()==0);
    
    /* Send results to client */
    std::string body;
    results.Compile(body);
    cmd.GetClient().SendBody(body);
    return result;
}

int o3cw::CO3CWBase::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out)
{
    /* Just do nothing */
    return 0;
}

int o3cw::CO3CWBase::StaticExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out)
{
    if (cmd.CmdAviable())
        cmd.Pop();
    return 0;
}

int o3cw::CO3CWBase::Open(o3cw::CCommand &cmd, o3cw::CCommand &out, o3cw::CO3CWBase **element)
{
    return 0;
}
