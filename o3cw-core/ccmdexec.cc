#include "ccmdexec.h"
#include "ccommand.h"
#include "cclient.h"

o3cw::CCmdExec::CCmdExec(): o3cw::CNetwork::CNetwork()
{
    Run();
}

o3cw::CCmdExec::~CCmdExec()
{
    Join();
}

int o3cw::CCmdExec::ThreadExecute()
{
    while (Killed()!=true)
    {
        cmd_bus.WaitForANewJob();
        
        if (cmd_bus.Destroyed())
            return 0;
        
        o3cw::CCommand *ptr_to_cmd=cmd_bus.GetJob();
	if (ptr_to_cmd!=NULL)
	{
    	    o3cw::CCommand &cmd=*ptr_to_cmd;
	    
            /* Decrypt command here.... */
	    	    
            /* (will be done later) */
            
            /* Parse it */
	    if (0==cmd.Parse())
            {
                /* ...and execute it. */
                int error=o3cw::CO3CWBase::PushCommand(cmd);

                if (error!=0)
                {
                        /* No normal answer send to client - send generic error to client */
                        cmd.GetClient().SendGenericError(error);
                }
            }
    	    /* Don't forget to free it! */
    	    delete &cmd;
	}
	else
	{
	    /* Just do nothing */
	}
    }
}
