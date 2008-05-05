// 
// File:   custorage.h
// Author: alex
//
// Created on 5 Май 2008 г., 20:23
//

#ifndef _CUSTORAGE_H
#define	_CUSTORAGE_H

#include "ccrypto.h"

namespace o3cw
{ 
    template <class T> class CUStorage: public o3cw::CSharedObject
    {
    public:
        CUStorage(){};
        virtual ~CUStorage()
        {
            for (std::map<o3cw::CHashKey, o3cw::CIdsObject *>::iterator it=store.begin() ; it!=store.end(); it++)
            {
                if (it->second!=NULL)
                    delete it->second;
            }
        }

	int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out)
        {
            int result=0;
            if (cmd.CmdAviable())
            {
                std::string &c1=cmd.Pop();

                cmd_out.Push(c1);

                 /* Get doc by unique adress (or id) hash */
                if (c1=="id")
                {

                    if (cmd.CmdAviable())
                    {
                        std::string &c4=cmd.Pop();
                        cmd_out.Push(c4.c_str());
                        std::string binmd5sum;
                        o3cw::CCrypto::Base64Decode(c4.c_str(), binmd5sum);
                        o3cw::CHashKey key(binmd5sum);

                        mlock.Lock();

                        std::map<o3cw::CHashKey, CIdsObject *>::const_iterator it=store.find(key);

                        mlock.UnLock();

                        if (it!=store.end())
                        {
                            if (cmd.CmdAviable())
                            {
                                std::string &c5=cmd.Pop();
                                /* Pass command queue to element */
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
                
                else if (c1=="open")
                {
                    if (cmd.CmdAviable())
                    {
                        std::string &c2=cmd.Pop();
                        printf("OPEN!\n");
                        cmd.Back(2);
                        if (T::StaticExecCommand(cmd, cmd_out)==0)
                        {
                            /* Get unique doc adress (or id) */
                            std::string md5sum;
                            o3cw::CCrypto::MD5HashBin(c2, md5sum);
                            o3cw::CHashKey key(md5sum);

                            /* Return id to client */
                            std::string b64md5sum;
                            o3cw::CCrypto::Base64Encode((const unsigned char*)md5sum.c_str(), md5sum.length(),b64md5sum);
                            cmd_out.Push(b64md5sum.c_str(), b64md5sum.length());

                            T *element=NULL;

                            mlock.Lock();

                            std::map <o3cw::CHashKey, o3cw::CIdsObject *>::const_iterator it=store.find(key);

                            /* No such doc opened - open it */
                            if (it==store.end())
                            {
                                element=new T();
                                printf(" * Opening new element, element adress=%p\n", element);
                                if (element!=NULL)
                                {
                                    element->SetId(b64md5sum);
                                    store.insert(std::pair<o3cw::CHashKey, T *>(key,element));

                                    mlock.UnLock();

                                    /*if (cmd.CmdAviable())
                                    {
                                        std::string &c3=cmd.Pop();
                                        if (c3=="do")
                                            element->ExecCommand(cmd, cmd_out);
                                    }*/
                                }
                                else
                                {
                                    mlock.UnLock();
                                    return O3CW_ERR_OUT_OF_MEM;
                                }
                            }

                            /* element opened already - just do nothing */
                            else if ((element=(dynamic_cast<T *>(it->second)))!=NULL)
                            {
                                mlock.UnLock();
                                printf(" * element opened already, element adress=%p\n", element);
                            }

                            /* element is NULL - WTF? */
                            else
                            {
                                mlock.UnLock();
                                return O3CW_ERR_NULL;
                            }
                            //cmd.Back(2);
                            element->ExecCommand(cmd, cmd_out);
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
            return result;
        }
        
    private:
        std::map<o3cw::CHashKey, o3cw::CIdsObject *> store;
	

    };
}

#endif	/* _CUSTORAGE_H */

