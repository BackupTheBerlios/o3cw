#include "ccommand.h"
#include "cclient.h"
#include "error.h"
#include "ccmdexec.h"

#define CMD_LEN_SIZE 4

o3cw::CCommand::CCommand(o3cw::CClient &cl, std::string *h, std::string *b)
{
    head=h;
    body=b;
    client=&cl;
    cl.Use();
    cur_val=cmds.begin();
    cmd_executor=NULL;
}

o3cw::CCommand::CCommand(o3cw::CClient &cl)
{
    head=NULL;
    body=NULL;
    client=&cl;
    cl.Use();
    cur_val=cmds.begin();
    cmd_executor=NULL;
}

o3cw::CCommand::CCommand(const o3cw::CCommand &cmd)
{
    head=NULL;
    body=NULL;
    client=cmd.client;
    if (client!=NULL)
        client->Use();
    cmds=cmd.cmds;
    cur_val=cmds.begin();
    cmd_executor=cmd.cmd_executor;
}

o3cw::CCommand::~CCommand()
{
    if (client!=NULL)
    {
        client->UnUse();
    }
    
}

o3cw::CClient &o3cw::CCommand::GetClient()
{
    return *client;
}

void o3cw::CCommand::Clear()
{
    cmds.clear();
    cur_val=cmds.begin();
}

int o3cw::CCommand::Parse()
{
    if (sizeof(size_t)<CMD_LEN_SIZE)
    {
	/* We are using wrong data type - report an error and exit */
	return -2;
    }
    
    if (body==NULL)
	return O3CW_ERR_NULL;

    bool stop=false;
    const char *msg=body->c_str();
    size_t msg_size=body->length();
    while (!stop)
    {
	if (msg_size<4)
        {
	    stop=true;
        }
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
		std::string b(msg,l);
		cmds.push_back(b);
		msg+=l;
		msg_size-=l;
	    }
	}
    }
    cur_val=cmds.begin();
    return 0;
}

std::string &o3cw::CCommand::Pop()
{
    std::string &result=*cur_val;
    if (cur_val!=cmds.end())
	cur_val++;
    return result;
}

void o3cw::CCommand::Back(int step)
{
    for (int i=0; i<step && cur_val!=cmds.begin(); i++)
        cur_val--;
}

int o3cw::CCommand::Compile(std::string &buff)
{
    std::vector<std::string>::iterator it;
    for (it=cmds.begin(); it<cmds.end(); it++)
    {
        std::string &c=*it;
        size_t size=c.length();
        char tmp[128];
        memcpy(tmp, &size, sizeof(size));
        buff.append(tmp, sizeof(size));
        buff.append(c);
    }
    return 0;
}

int o3cw::CCommand::Push(std::string &data)
{
    cmds.push_back(data);
    return 0;
}

int o3cw::CCommand::Push(int number)
{
    char tmp[128];
    snprintf(tmp, 128, "%i", number);
    return Push(tmp);
}

int o3cw::CCommand::Push(const char *data)
{
    if (data==NULL)
        return -1;
    std::string s(data);
    cmds.push_back(s);
    return 0;
}

int o3cw::CCommand::Push(const char*data, size_t data_size)
{
    std::string s(data, data_size);
    cmds.push_back(s);
    return 0;
}

void o3cw::CCommand::FreeCryptedData()
{
    if (body!=NULL)
    {
	delete body;
	body=NULL;
    }

    if (head!=NULL)
    {
	delete head;
	head=NULL;
    }
}

bool o3cw::CCommand::CmdAviable()
{
    if (cur_val!=cmds.end())
	return true;
    return false;
}

int o3cw::CCommand::SetExecutor(o3cw::CCmdExec &executor)
{
    cmd_executor=&executor;
    return 0;
}

o3cw::CCmdExec &o3cw::CCommand::GetExecutor()
{
    return *cmd_executor;
}
