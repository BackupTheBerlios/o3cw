#include "cnetwork.h"

//std::vector<o3cw::CClient *> o3cw::CNetwork::clients;
bonbon::CJobManager<o3cw::CCommand *> o3cw::CNetwork::cmd_bus;

o3cw::CNetwork::CNetwork(): bonbon::CThread::CThread(), o3cw::CO3CWBase::CO3CWBase()
{
    
}

o3cw::CNetwork::~CNetwork()
{
    
}
