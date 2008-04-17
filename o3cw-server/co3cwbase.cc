#include "co3cwbase.h"

o3cw::CConfig o3cw::CO3CWBase::o3cw_main_config;

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
