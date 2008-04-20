#include "ccmdexec.h"
#include "ccommand.h"

o3cw::CCmdExec::CCmdExec(): o3cw::CNetwork::CNetwork()
{
    
}

o3cw::CCmdExec::~CCmdExec()
{
    
}

int o3cw::CCmdExec::ThreadExecute()
{
    while (Killed()!=true)
    {
        cmd_bus.WaitForANewJob();
        o3cw::CCommand &cmd=*cmd_bus.GetJob();
        
        /* Decrypt command here.... */
        
        /* ...and execute it. */
        o3cw::CO3CWBase::PushCommand(cmd);
        
        /* Don't forget to free it! */
        delete &cmd;
    }
}
