#include "co3cwbase.h"
#include "cconfig.h"
#include "ccommand.h"

o3cw::CConfig o3cw::CO3CWBase::o3cw_main_config;
o3cw::CO3CWBase *o3cw::CO3CWBase::server=NULL;
        
o3cw::CO3CWBase::CO3CWBase(): o3cw::CInTimeObject::CInTimeObject()
{

}

o3cw::CO3CWBase::~CO3CWBase()
{
    
}

int o3cw::CO3CWBase::LoadMainConfig(const char *filename)
{
    int result=0;
//    mlock.Lock();
    o3cw_main_config.ParseFile(filename);
//    mlock.UnLock();
    return result;
}

int o3cw::CO3CWBase::ReLoadMainConfig(const char *filename)
{
    return LoadMainConfig(filename);
}

const o3cw::CConfig &o3cw::CO3CWBase::GetMainConfig()
{
    return o3cw_main_config;
}

int o3cw::CO3CWBase::PushCommand(o3cw::CCommand &cmd)
{
    /* Parse command and push it further */

    int result=o3cw::CO3CWBase::server->ExecCommand(cmd);
    while (cmd.cmds.size()>0)
    {
        std::string *s=cmd.cmds.front();
        if (s!=NULL)
            delete s;
        cmd.cmds.pop();
    }

    
    return 0;
}

int o3cw::CO3CWBase::ExecCommand(o3cw::CCommand &cmd)
{
    /* Just do nothing */
    return 0;
}
