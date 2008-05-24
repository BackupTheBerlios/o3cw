#include "cnetwork.h"
#include "ccommand.h"

//std::vector<o3cw::CClient *> o3cw::CNetwork::clients;
bonbon::CJobManager<o3cw::CCommand *> o3cw::CNetwork::cmd_bus;

o3cw::CNetwork::CNetwork(): bonbon::CThread::CThread(), o3cw::CO3CWBase::CO3CWBase()
{
    
}

o3cw::CNetwork::~CNetwork()
{
    
}

void o3cw::CNetwork::Cleanup()
{
    while (cmd_bus.GetJobsCount()>0)
    {
        o3cw::CCommand *cmd=cmd_bus.GetJob();
        if (cmd!=0)
            delete cmd;
    }
}
