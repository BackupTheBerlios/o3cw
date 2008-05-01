#include "cstorage.h"
#include "ccommand.h"
#include "cdoc.h"
#include "ccrypto.h"
#include "error.h"

o3cw::CStorage::CStorage()
{
}

o3cw::CStorage::~CStorage()
{
    for (std::map<o3cw::CHashKey, o3cw::CDoc *>::iterator it=docs.begin() ; it != docs.end(); it++)
    {
        if (it->second!=NULL)
            delete it->second;
    }
}

int o3cw::CStorage::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out)
{
    if (cmd.CmdAviable())
    {
	std::string &c1=cmd.Pop();
	
	cmd_out.Push(c1);
	
	/* Open new doc */
        if (c1=="open")
        {
	    /* Get unique doc adress (or id) */
	    if (cmd.CmdAviable())
            {
		std::string &c2=cmd.Pop();
                std::string md5sum;
                o3cw::CCrypto::MD5HashBin(c2, md5sum);
                o3cw::CHashKey key(md5sum);
                
                /* Return id to client */
                std::string b64md5sum;
                o3cw::CCrypto::Base64Encode((const unsigned char*)md5sum.c_str(), md5sum.length(),b64md5sum);
                cmd_out.Push(b64md5sum.c_str(), b64md5sum.length());
		
                o3cw::CDoc *doc=NULL;
		
                mlock.Lock();
                
                std::map<o3cw::CHashKey, o3cw::CDoc *>::const_iterator it=docs.find(key);
                
                /* No such doc opened - open it */
                if (it==docs.end())
                {
                    doc=new o3cw::CDoc();
                    printf(" * Opening new doc, doc adress=%p\n", doc);
                    if (doc!=NULL)
                    {
			doc->SetId(b64md5sum);
                        docs.insert(std::pair<o3cw::CHashKey, o3cw::CDoc *>(key,doc));
                        
                        mlock.UnLock();
			
                        if (cmd.CmdAviable())
                        {
			    std::string &c3=cmd.Pop();
                            /* Pass command queue to opened doc */
                            if (c3=="do")
                                doc->ExecCommand(cmd, cmd_out);
                        }
                    }
                    else
                    {
                        mlock.UnLock();
                        return O3CW_ERR_OUT_OF_MEM;
                    }
                }
                
                /* Doc opened already - just do nothing */
                else if ((doc=it->second)!=NULL)
                {
                    mlock.UnLock();
                    printf(" * Doc opened already, doc adress=%p\n", doc);
                }
		    
		/* Doc is NULL - WTF? */
		else
                {
                    mlock.UnLock();
		    return O3CW_ERR_NULL;
                }
		    
		doc->Open(cmd.GetClient());
            }
        }
	
        /* Get doc by unique adress (or id) hash */
        else if ("id")
        {
	    
	    if (cmd.CmdAviable())
            {
		std::string &c4=cmd.Pop();
                cmd_out.Push(c4.c_str());
                std::string binmd5sum;
                o3cw::CCrypto::Base64Decode(c4.c_str(), binmd5sum);
                o3cw::CHashKey key(binmd5sum);
                
                mlock.Lock();
                
                std::map<o3cw::CHashKey, o3cw::CDoc *>::const_iterator it=docs.find(key);

                mlock.UnLock();
                
                if (it!=docs.end())
                {
		    if (cmd.CmdAviable())
                    {
			std::string &c5=cmd.Pop();
                        /* Pass command queue to doc */
                        if (c5=="do")
                            it->second->ExecCommand(cmd, cmd_out);
                    }
                }
                 /* No such doc */
                else
                {
		    cmd_out.Push("error");
		    cmd_out.Push("not found");
                }
            }
        }
	else
	{
	    cmd_out.Pop();
	    cmd_out.Push("error");
	    cmd_out.Push("not found");
	}
    }
}
