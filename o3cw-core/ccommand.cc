#include "ccommand.h"
#include "cclient.h"
#include "error.h"

#define CMD_LEN_SIZE 4

o3cw::CCommand::CCommand(o3cw::CClient &cl, std::string &data)
{
    crypted_data.assign(data);
    client=&cl;
}

o3cw::CCommand::CCommand(o3cw::CClient &cl)
{
    client=&cl;
}

o3cw::CCommand::~CCommand()
{
    
}
o3cw::CClient &o3cw::CCommand::GetClient()
{
    return *client;
}

int o3cw::CCommand::Parse()
{
    if (sizeof(size_t)<CMD_LEN_SIZE)
    {
	/* We are using wrong data type - report an error and exit */
	return -2;
    }

    bool stop=false;
    
    const char *msg=crypted_data.c_str();
    size_t msg_size=crypted_data.length();
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
		    return O3CW_ERR_OUT_OF_MEM;
		}
	    }
	}
        if (msg_size==0)
            stop=true;
    }
    return 0;
}

int o3cw::CCommand::Pop(std::string &buff)
{
    if (cmds.size()>0)
    {
        std::string *c=cmds.front();
        cmds.pop();
        if (c!=NULL)
        {
            buff.assign(*c);
	    delete c;
	}
	else
	    return -1;
	return 0;	
    }
    return -2;
}

int o3cw::CCommand::Get(std::string &buff)
{
    if (cmds.size()>0)
    {
        std::string *c=cmds.front();
        if (c!=NULL)
            buff=*c;
	else
	    return -1;
	return 0;	
    }
    return -2;
}

int o3cw::CCommand::Pop()
{
    if (cmds.size()>0)
    {
        std::string *c=cmds.front();
        cmds.pop();
        if (c!=NULL)
	    delete c;
	else
	    return -1;
	return 0;	
    }
    return -2;
}

int o3cw::CCommand::Compile(std::queue<std::string *> &c, std::string &buff)
{
    buff.erase();
    while (c.size()>0)
    {
        std::string *p=c.front();
        c.pop();
        if (p!=NULL)
        {
            std::string &s=*p;
            size_t size=s.length();
            char tmp[128];
            memcpy(tmp, &size, sizeof(size));
            buff.append(tmp, sizeof(size));
            buff.append(s);
            delete p;
        }
    }
    return 0;
}

int o3cw::CCommand::Compile(std::string &buff)
{
    while (cmds.size()>0)
    {
        std::string *c=cmds.front();
        cmds.pop();
        if (c!=NULL)
        {
            std::string &s=*c;
            size_t size=s.length();
            char tmp[128];
            memcpy(tmp, &size, sizeof(size));
            buff.append(tmp, sizeof(size));
            buff.append(s);
            delete c;
        }
    }
    return 0;
}

int o3cw::CCommand::Push(std::string &data)
{
    cmds.push(&data);
}

int o3cw::CCommand::Push(const char*data)
{
    if (data==NULL)
        return -1;
    std::string *s=new std::string(data);
    cmds.push(s);
}

int o3cw::CCommand::Push(const char*data, size_t data_size)
{
    if (data==NULL)
        return -1;
    std::string *s=new std::string(data, data_size);
    cmds.push(s);
}
