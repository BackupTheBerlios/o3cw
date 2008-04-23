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
    std::string c;
    if (cmd.Pop(c)==0)
    {
        /* Open new doc */
        if (c=="open")
        {
            /* Get unique doc adress (or id) */
            if (cmd.Pop(c)==0)
            {
                std::string md5sum;
                o3cw::CCrypto::MD5HashBin(c, md5sum);
                o3cw::CHashKey key(md5sum);
                std::map<o3cw::CHashKey, o3cw::CDoc *>::iterator it=docs.find(key);
                
                /* Return id to client */
                std::string b64md5sum;
                o3cw::CCrypto::Base64Encode((const unsigned char*)md5sum.c_str(), md5sum.length(),b64md5sum);
                cmd_out.Push(b64md5sum.c_str(), b64md5sum.length());
                
                /* No such doc opened - open it */
                if (it==docs.end())
                {   
                    o3cw::CDoc *doc=new o3cw::CDoc();
                    printf("Opening new doc, doc adress=%p\n", doc);
                    if (doc!=NULL)
                    {
                        docs.insert(std::pair<o3cw::CHashKey, o3cw::CDoc *>(key,doc));
                        if (cmd.Pop(c)==0)
                        {
                            /* Pass command queue to opened doc */
                            if (c=="do")
                                doc->ExecCommand(cmd, cmd_out);
                        }
                    }
                    else
                        return O3CW_ERR_OUT_OF_MEM;
                }
                
                /* Doc opened already - just do nothing */
                else
                {
                    printf("Doc opened already, doc adress=%p\n", it->second);
                }
            }
        }
        /* Get doc by unique adress (or id) hash */
        else if ("id")
        {
            if (cmd.Pop(c)==0)
            {
                cmd_out.Push(c.c_str());
                std::string binmd5sum;
                o3cw::CCrypto::Base64Decode(c.c_str(), binmd5sum);
                o3cw::CHashKey key(binmd5sum);
                std::map<o3cw::CHashKey, o3cw::CDoc *>::iterator it=docs.find(key);
                if (it!=docs.end())
                {
                    if (cmd.Pop(c)==0)
                    {
                        /* Pass command queue to doc */
                        if (c=="do")
                            it->second->ExecCommand(cmd, cmd_out);
                    }
                }
                 /* No such doc */
                else
                {
                    printf("doc not found\n");
                }
            }
        }
    }
}
