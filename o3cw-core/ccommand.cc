#include "ccommand.h"
#include "cclient.h"

#define CMD_LEN_SIZE 4

o3cw::CCommand::CCommand()
{
    client=NULL;
}

o3cw::CCommand::~CCommand()
{
    
}

int o3cw::CCommand::Parse()
{
    if (sizeof(size_t)<CMD_LEN_SIZE)
    {
	/* We are using wrong data type - report an error and exit */
	return -2;
    }

    bool stop=false;
    
    const char *msg=crypted_cmd.c_str();
    size_t msg_size=crypted_cmd.length();
    while (!stop)
    {
	if (msg_size<4)
	    stop=true;
	else
	{
    	    size_t l=0;
	    memcpy(&l, msg, CMD_LEN_SIZE);
	    msg+=CMD_LEN_SIZE;
	    msg_size-=4;
	    if (msg_size<l)
		stop=true;
	    else
	    {
		std::string *b=new std::string();
		if (b!=NULL)
		{
		    b->assign(msg, l);
		    cmds.push(b);
		    msg+=l;
		    msg_size-=l;
		}
		else
		{
		    /* Out of mem */
		    return -1;
		}
	    }
	}
        if (msg_size==0)
            stop=true;
    }
    return 0;
}
