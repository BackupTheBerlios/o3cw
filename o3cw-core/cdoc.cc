#include <fstream>

#include "cdoc.h"
#include "cclient.h"
#include "cdiff.h"
#include "error.h"
#include "ccommand.h"

o3cw::CUniqueAux o3cw::CDoc::unique_data;

o3cw::CDoc::CDoc(): o3cw::CIdsObject::CIdsObject(o3cw::CDoc::unique_data)
{
    o3cw::ids parts_current_id=0;
    
    /* Every document contains at least one part - create it */
    o3cw::CDocPart *new_part=new o3cw::CDocPart(parts_unique_aux);
    parts.push_back(new_part);
}

o3cw::CDoc::~CDoc()
{
    /* Clean up all diffs */
    std::vector<o3cw::CDocPart *>::iterator it;
    for (it=parts.begin(); it!=parts.end(); it++)
        delete *it;
}

int o3cw::CDoc::OpenFile(const char *filename)
{
    int result=O3CW_ERR_BAD_FILE;
    std::ifstream is;
    is.open (filename, std::ios::binary);
    if (is.good())
    {
        is.seekg (0, std::ios::end);
        int length=is.tellg();
        is.seekg (0, std::ios::beg);
        char *buffer = new char [length];
        if (buffer!=NULL)
        {
            is.read (buffer,length);
            content.assign(buffer, length);
            delete [] buffer;
            result=0;
        }
        else
            result=O3CW_ERR_OUT_OF_MEM;
    }
    is.close();
    return result;
}

int o3cw::CDoc::GetData(CClient &client, std::string &buff)
{
    buff.assign(content);
    return 0;
}

int o3cw::CDoc::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out)
{
    while (cmd.CmdAviable())
    {
	std::string &c1=cmd.Pop();
        printf("next cmd in queue=[%s]\n", c1.c_str());
        if (c1=="get")
        {
            cmd_out.Push(c1);
            cmd_out.Push(content.c_str());
        }
        else if (c1=="load")
        {
	    if (cmd.CmdAviable())
            {
		std::string c2=cmd.Pop();
                OpenFile(c2.c_str());
            }
        }
	else if (c1=="commit")
	{
	    if (cmd.CmdAviable())
	    {
		std::string c2=cmd.Pop();
		content=c2;
		
		o3cw::CCommand multi_cmd(cmd_out);

		multi_cmd.Push("changed");
	        MultiCast(multi_cmd);
	    }
	}
    }
}

int o3cw::CDoc::Open(o3cw::CClient &client)
{
    std::vector<o3cw::CClient *>::iterator it=clients_connected.begin();
    while (it<clients_connected.end())
    {
	if (*it==&client)
	{
	    printf(" * This user connected already to this doc\n");
	    return -1;
	}
	it++;
    }
    printf(" * Compiling answer...\n");
    o3cw::CCommand cmd(client);
    char tmp[128];
    snprintf(tmp,128, "%i", client.GetFD());
    
    cmd.Push("client");
    cmd.Push(tmp);
    cmd.Push("connected");
    MultiCast(cmd);
    
    printf(" * Add user to online docs user\n");
    clients_connected.push_back(&client);
    printf(" * Done\n");
    return 0;
}

int o3cw::CDoc::MultiCast(o3cw::CCommand &cmd)
{
    printf(" * Multicast\n");
    std::string buff;
    cmd.Compile(buff);
    std::vector<o3cw::CClient *>::iterator it=clients_connected.begin();
    it=clients_connected.begin();
    while (it<clients_connected.end() && (*it)!=NULL)
    {
        (*it)->SendBody(buff);
	it++;
    }
    return 0;    
}

int o3cw::CDoc::SetId(std::string &new_id)
{
    id=new_id;
    return 0;
}
