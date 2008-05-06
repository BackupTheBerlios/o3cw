#include <fstream>

#include "cdoc.h"
#include "cclient.h"
#include "cdiff.h"
#include "error.h"
#include "ccommand.h"
#include "csql.h"
#include "ccmdexec.h"
#include "cuser.h"

o3cw::CUniqueAux o3cw::CDoc::unique_data;

o3cw::CDoc::CDoc(): o3cw::CIdsObject::CIdsObject(o3cw::CDoc::unique_data)
{
    /* Every document contains at least one part - create it */
    o3cw::CDocPart *new_part=new o3cw::CDocPart(parts_unique_aux);
    parts.push_back(new_part);
}

o3cw::CDoc::~CDoc()
{
    /* Clean up all diffs */
    std::vector<o3cw::CDocPart *>::iterator it;
    for (it=parts.begin(); it<parts.end(); it++)
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
    int result=0;
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
        else if (c1=="open")
        {
            Open(cmd.GetClient());
        }
    }
    return result;
}

int o3cw::CDoc::Open(o3cw::CClient &client)
{
    mlock.Lock();
    std::vector<o3cw::CClient *>::iterator it=clients_connected.begin();
    while (it<clients_connected.end())
    {
	if (*it==&client)
	{
	    printf(" * This user connected already to this doc\n");
            mlock.UnLock();
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
    
    printf(" * Add user to online docs user\n");
    clients_connected.push_back(&client);
    client.OpenDoc(*this);
    printf(" * Done\n");
    mlock.UnLock();
    
    MultiCast(cmd);
    
    return 0;
}

int o3cw::CDoc::MultiCast(o3cw::CCommand &cmd)
{
    printf(" * Multicast\n");
    std::string buff;
    cmd.Compile(buff);
    
    mlock.Lock();
    std::vector<o3cw::CClient *>::iterator it=clients_connected.begin();
    it=clients_connected.begin();
    while (it<clients_connected.end() && (*it)!=NULL)
    {
        (*it)->SendBody(buff);
        printf(" * Send data to %p\n", *it);
	it++;
    }
    mlock.UnLock();
    printf(" * Multicast done\n");
    return 0;    
}

int o3cw::CDoc::RemoveClientFromMulticast(const o3cw::CClient &client)
{
    mlock.Lock();
    std::vector<o3cw::CClient *>::iterator it=clients_connected.begin();
    for (it=clients_connected.begin(); it<clients_connected.end(); it++)
    {
        if (*it==&client)
        {
            clients_connected.erase(it);
            printf(" * Client removed from multicast\n");
            mlock.UnLock();
            return 0;
        }
    }
    mlock.UnLock();
    return -1;
}

int o3cw::CDoc::Open(o3cw::CCommand &cmd, o3cw::CCommand &out, o3cw::CO3CWBase **element)
{
    o3cw::CDoc *doc=dynamic_cast<o3cw::CDoc *>(*element);
    int result=O3CW_ERR_DENIED;
    result=0;
    if (cmd.CmdAviable())
    {
        std::string &c1=cmd.Pop();
        if (c1=="open")
        {
            if (cmd.CmdAviable())
            {
                std::string &c2=cmd.Pop();
                
                o3cw::CSQL &sql=cmd.GetExecutor().SQL();
                std::string request("select user_id from docs_perm where doc_id='");
                request+=sql.SQLSafeStr(c2);
                request+="'";
                
                sql.SQLRequest(request);
                
                std::vector <std::string> sql_result;
                bool doc_acess=false;
                while (cmd.GetExecutor().SQL().GetNextDataSet(sql_result)==0)
                {
                    std::string username;
                    o3cw::CUser *user=cmd.GetClient().GetUser();
                    if (user!=NULL)
                    {
                        if (atol(sql_result[0].c_str())==user->GetUserId())
                        {
                            /* Permission OK */
                            doc_acess=true;
                        }
                    }
                }
                
                if (doc_acess==false)
                {
                    printf("ACESS DENIED\n");
                    result=O3CW_ERR_DENIED;
                }
                else
                {
                    if (doc==NULL)
                    {
                        /* Doc doesnt exist in store */
                        doc=new o3cw::CDoc();
                    }
                }
                cmd.Back();
            }
        }
        cmd.Back();
    }
    *element=dynamic_cast<o3cw::CO3CWBase *>(doc);
    return result;
}

int o3cw::CDoc::StaticExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out)
{
    int result=O3CW_ERR_DENIED;
     if (cmd.CmdAviable())
    {
        std::string &c1=cmd.Pop();
        if (c1=="list")
        {
            o3cw::CSQL &sql=cmd.GetExecutor().SQL();
            long userid=-1;
            o3cw::CUser *user=cmd.GetClient().GetUser();
            if (user!=NULL)
            {
                userid=user->GetUserId();
                std::string request("select doc_id from docs_perm where user_id='");
                request+=sql.SQLSafeStr(userid);
                request+="'";
                sql.SQLRequest(request);
                std::vector <std::string> sql_result;
                while (cmd.GetExecutor().SQL().GetNextDataSet(sql_result)==0)
                    out.Push(sql_result[0]);

                result=0;
            }
        }
     }
     return 0;
}
