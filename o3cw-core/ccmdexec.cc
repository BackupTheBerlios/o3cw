#include "ccmdexec.h"
#include "ccommand.h"
#include "cclient.h"
#include "csql.h"

o3cw::CCmdExec::CCmdExec(): o3cw::CNetwork::CNetwork()
{

}

o3cw::CCmdExec::~CCmdExec()
{
    Join();
}

int o3cw::CCmdExec::Run(o3cw::CSQL &sql_connection)
{
    m_sql_connection=&sql_connection;
    return o3cw::CNetwork::Run();
}

o3cw::CSQL &o3cw::CCmdExec::SQL()
{
    return *m_sql_connection;
}

void o3cw::CCmdExec::CleanUp()
{
    m_sql_connection->ThreadEnd();
}

int o3cw::CCmdExec::ThreadExecute()
{
//    m_sql_connection->ThreadStart();
    while (Killed()!=true)
    {
        cmd_bus.WaitForANewJob();
        
        if (cmd_bus.Destroyed())
        {
            CleanUp();
            return 0;
        }
        
        o3cw::CCommand *ptr_to_cmd=cmd_bus.GetJob();
	if (ptr_to_cmd!=NULL)
	{
    	    o3cw::CCommand &cmd=*ptr_to_cmd;
	    cmd.SetExecutor(*this);
            
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
	    cmd.FreeCryptedData();
    	    delete &cmd;
	}
	else
	{
	    /* Just do nothing */
	}
    }
    CleanUp();
    return 0;
}
