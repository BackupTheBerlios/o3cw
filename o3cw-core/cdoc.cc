#include <fstream>
#include <assert.h>

#include "cdoc.h"
#include "cclient.h"
#include "cdiff.h"
#include "error.h"
#include "ccommand.h"
#include "csql.h"
#include "ccmdexec.h"
#include "cuser.h"
#include "cdocpart.h"

o3cw::CUniqueAux o3cw::CDoc::unique_data;

o3cw::CDoc::CDoc(): o3cw::CIdsObject::CIdsObject(o3cw::CDoc::unique_data)
{
    /* Every document contains at least one part - create it */
    o3cw::CDocPart *new_part=new o3cw::CDocPart(*this);
    m_parts.push_back(new_part);
}

o3cw::CDoc::~CDoc()
{
    /* Clean up all diffs */
    std::vector<o3cw::CDocPart *>::iterator it;
    for (it=m_parts.begin(); it<m_parts.end(); it++)
    {
	if (*it!=NULL)
	    delete *it;
    }
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
            else
                result=O3CW_ERR_BAD_SEQ;
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
            else
                result=O3CW_ERR_BAD_SEQ;
	}
        else if (c1=="open")
        {
            o3cw::CClient &client=cmd.GetClient();
            mlock.Lock();
            std::vector<o3cw::CClient *>::iterator it=clients_connected.begin();
            while (it<clients_connected.end())
            {
                if (*it==&client)
                {
                    printf(" * This user connected already to this doc\n");
                    result=O3CW_ERR_DUBLICATE;
                    it=clients_connected.end();
                }
                it++;
            }
            
            if (0==result)
            {
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
            }
            mlock.UnLock();
            if (0==result)
                MultiCast(cmd);
        }
        else if (c1=="part")
        {
            if (cmd.CmdAviable())
            {
                std::string &c2=cmd.Pop();
                if (c2=="id")
                {
                    if (cmd.CmdAviable())
                    {
                        std::string &c_id=cmd.Pop();
                        
                        /* Search part with a specified id */
                        
                        if (cmd.CmdAviable())
                        {
                            std::vector<o3cw::CDocPart *>::iterator search_it;
                            for (search_it=m_parts.begin(); search_it<m_parts.end(); search_it++)
                            {
                                o3cw::CDocPart *dpart=*search_it;
                                std::string cur_key;
                                if (dpart!=NULL && dpart->GetKey().GetBase64Value(cur_key)==c_id)
                                {
                                    std::string &c_do=cmd.Pop();
                                    if (c_do=="do")
                                    {
                                        result=dpart->ExecCommand(cmd, cmd_out);
                                    }
                                    else
                                        result=O3CW_ERR_BAD_SEQ;
                                }
                            }
                        }
                        else
                            result=O3CW_ERR_BAD_SEQ;
                    }
                    else
                        result=O3CW_ERR_BAD_SEQ;
                }
                else
                    result=O3CW_ERR_BAD_SEQ;
            }
            else
                result=O3CW_ERR_BAD_SEQ;
        }
    }
    return result;
}

int o3cw::CDoc::MultiCast(o3cw::CCommand &cmd) const
{
    printf(" * Multicast\n");
    std::string buff;
    cmd.Compile(buff);
    
    mlock.Lock();
    std::vector<o3cw::CClient *>::const_iterator it=clients_connected.begin();
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
    for (std::vector<o3cw::CClient *>::iterator it=clients_connected.begin(); it<clients_connected.end(); it++)
    {
        if (*it==&client)
        {
            clients_connected.erase(it);
            printf(" * Client removed from multicast\n");
	    
	    /* Call Remove Client From Multicast from all parts */
	    for (std::vector<o3cw::CDocPart *>::iterator docpart_it=m_parts.begin(); docpart_it<m_parts.end(); docpart_it++)
	    {
		o3cw::CDocPart *docpart=(*docpart_it);
		docpart->Use();
		mlock.UnLock();
		
		(*docpart_it)->RemoveClientFromMulticast(client);
		
		mlock.Lock();
		docpart->UnUse();
	    }
	    mlock.UnLock();
            
            return 0;
        }
    }
    mlock.UnLock();
    return -1;
}

int o3cw::CDoc::Open(o3cw::CCommand &cmd, o3cw::CCommand &out, o3cw::CIdsObject **element)
{
    o3cw::CDoc *doc=dynamic_cast<o3cw::CDoc *>(*element);
    
    assert(*element==NULL || doc!=NULL);
    
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
                
                if (0==sql.SQLRequest(request))
		{
                
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
		}
		else
		{
		    result=O3CW_ERR_DB;
		}
                cmd.Back();
            }
        }
        cmd.Back();
    }
    *element=dynamic_cast<o3cw::CIdsObject *>(doc);
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
