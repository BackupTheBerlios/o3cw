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
                        int create_new_element=0;
                        std::string &c2=cmd.Pop();
                        cmd.Back(2);

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
                            o3cw::CO3CWBase *tmp=NULL;
                            if ((create_new_element=T::Open(cmd, cmd_out, &tmp))==0)
                            {
                                element=dynamic_cast<T *>(tmp);
                                printf(" * Opening new element, element adress=%p\n", element);
                                if (element!=NULL)
                                {
                                    element->SetKey(key);
                                    store.insert(std::pair<o3cw::CHashKey, T *>(key,element));


                                }
                                else
                                {
                                    result=O3CW_ERR_OUT_OF_MEM;
                                }
                            }
                            else
                            {
                                if (element!=NULL)
                                {
                                    printf("WARNING: Got and error while creating new element but result not NULL. Fix it!\nAutdelete it now...\n");
                                    delete element;
                                }
                                printf("Error %i while creating new element\n",create_new_element);
                                result=create_new_element;
                            }
                        }

                        /* Element opened already */
                        else if ((element=(dynamic_cast<T *>(it->second)))!=NULL)
                        {
                            o3cw::CO3CWBase *tmp=dynamic_cast<o3cw::CO3CWBase *>(element);
                            create_new_element=T::Open(cmd, cmd_out, &tmp);
                            
                            /* Check if new element created by a mistake */
                            T* new_e=dynamic_cast<T *>(tmp);
                            if (new_e!=element)
                            {
                                printf("WARNING: wrong behaviour: new element created. Fix it!\nAutdelete it now...\n");
                                delete new_e;
                            }
                            
                            if (create_new_element==0)
                            {
                                /* Client can open it */
                                printf(" * element opened already, element adress=%p\n", element);
                            }
                            else
                            {
                                /* Client can NOT open it */
                                
                                printf("Error %i while opening existing element\n",create_new_element);
                                result=create_new_element;
                            }
                        }

                        /* element is NULL - WTF? */
                        else
                        {
                            printf("error while dynamic_cast\n");
                            result=O3CW_ERR_NULL;
                        }
                        printf("mlock=%p\n", &mlock);

                        if (element!=NULL)
                        {
                            element->ExecCommand(cmd, cmd_out);
                        }
                        mlock.UnLock();
                    }
                }
                else
                {
                    cmd.Back();
                    result=T::StaticExecCommand(cmd, cmd_out);
                 /*   cmd_out.Pop();
                    cmd_out.Push("error");
                    cmd_out.Push("not found");*/
                }
            }
            DeleteUnusedElements();
            return result;
        }
        
        void DeleteUnusedElements()
        {
            /* THIS CODE CAN BE MOVED TO A SEPARATED FUNCTION "CLEANUP" */
            printf("delete list size=%u\n", T::delete_list.size());
            std::vector<o3cw::CIdsObject *>::iterator delete_unused_it;
            T::class_mlock.Lock();
            mlock.Lock();
            for (delete_unused_it=T::delete_list.begin(); delete_unused_it<T::delete_list.end();delete_unused_it++)
            {
                o3cw::CHashKey key((*delete_unused_it)->GetKey());
                std::map<o3cw::CHashKey, CIdsObject *>::iterator it=store.find(key);

                if (it!=store.end())
                {
                    if (it->second->GetUseCount()==0)
                    {
                        /* Element really unused - delete it. */
                        printf(" * Deleting element cause unused\n");
                        delete it->second;
                        store.erase(it);
                    }
                    else
                    {
                        /* Still used - just delete from unused list */
                    }
                    T::delete_list.erase(delete_unused_it);
                }
                else
                    printf("Element not found in list\n");
            }
            mlock.UnLock();
            T::class_mlock.UnLock();
            /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */            
        }
    private:
        std::map<o3cw::CHashKey, o3cw::CIdsObject *> store;
	

    };
}

#endif	/* _CUSTORAGE_H */

