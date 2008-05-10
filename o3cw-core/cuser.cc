#include <algorithm>
 #include <assert.h>

#include "cuser.h"
#include "cclient.h"
#include "ccommand.h"
#include "ccmdexec.h"
#include "csql.h"
#include "cconfig.h"
#include "error.h"

o3cw::CUniqueAux o3cw::CUser::unique_data;

o3cw::CUser::CUser(): o3cw::CIdsObject::CIdsObject(unique_data)
{
    m_user_id=-1;
}

o3cw::CUser::CUser(long user_id): o3cw::CIdsObject::CIdsObject(unique_data)
{
    m_user_id=user_id;
}

o3cw::CUser::~CUser()
{
    
}

void o3cw::CUser::GetName(std::string &buff)
{
    mlock.Lock();
    buff=m_name;
    mlock.UnLock();
}

int o3cw::CUser::Open(o3cw::CCommand &cmd, o3cw::CCommand &out, o3cw::CIdsObject **element)
{
    o3cw::CUser *user=dynamic_cast<o3cw::CUser *>(*element);
    
    assert(*element==NULL || user!=NULL);
    
    int result=O3CW_ERR_DENIED;
    if (cmd.CmdAviable())
    {
        std::string &c1=cmd.Pop();
        if (c1=="open")
        {
            if (cmd.CmdAviable())
            {
                std::string &c2=cmd.Pop();
                printf("loggin as [%s]\n",c2.c_str());
                std::string admin_password("");
                std::string admin_name("admin");
                o3cw::CO3CWBase::GetMainConfig().GetValue(admin_name, "name", "authorization:admin");
                o3cw::CO3CWBase::GetMainConfig().GetValue(admin_password, "password", "authorization:admin");
                if (cmd.CmdAviable())
                {
                    if (c2==admin_name)
                    {
                        if (cmd.Pop()==admin_password)
                        {
                            printf("Access granted. Hello, admin\n");
                            result=0;
                            cmd.Back();
                            
                            if (user==NULL)
                                user=new o3cw::CUser();
                        }
                    }
                    else
                    {
                        o3cw::CSQL &sql=cmd.GetExecutor().SQL();
                        std::string login=c2;
                        
                        /* Prepearin request string */
                        std::string request("select password, user_id from users where name='");
                        request+=sql.SQLSafeStr(login);
                        request+="'";
                        
                        /* Performing a SQL request */
                        sql.SQLRequest(request);
                        
                        std::vector <std::string> sql_result;
                        if (cmd.GetExecutor().SQL().GetNextDataSet(sql_result)==0)
                        {
                            std::string &c3=cmd.Pop();
                            if (c3==sql_result[0])
                            {
                                printf("Access granted\n");
                                result=0;
                                if (user==NULL)
                                    user=new o3cw::CUser(atol(sql_result[1].c_str()));
                            }
                            else
                            {
                                printf("Access denied\n");
                            }
                            cmd.Back();
                        }
                        else
                        {
                            /* No such user */
                            printf("Access denied\n");
                        }
                    }
                }
                else
                {
                    if (c2==admin_name && admin_password=="")
                    {
                        printf("Access granted. Hello, admin. Your password is empty - change it, please.\n");
                        result=0;
                        if (user==NULL)
                            user=new o3cw::CUser();
                    }
                }
                cmd.Back();
            }
        }
        cmd.Back();
    }
    *element=dynamic_cast<o3cw::CIdsObject *>(user);
    return result;
}

int o3cw::CUser::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out)
{
    if (cmd.CmdAviable())
    {
        std::string &c1=cmd.Pop();
        if (c1=="open")
        {
            cmd.GetClient().SetUser(*this);
        }
        
        if (cmd.CmdAviable())
        {
            std::string &c2=cmd.Pop();
            mlock.Lock();
            m_name=c2;
            mlock.UnLock();
        }
    }
    return 0;
}

long o3cw::CUser::GetUserId() const
{
    mlock.Lock();
    long result=m_user_id;
    mlock.UnLock();
    return result;
}

int o3cw::CUser::ClientRegister(o3cw::CClient &client)
{
    mlock.Lock();
    if (std::find(m_clients.begin(), m_clients.end(), &client)==m_clients.end())
        m_clients.push_back(&client);
    mlock.UnLock();
    Use();
    return 0;
}

int o3cw::CUser::ClientUnRegister(o3cw::CClient &client)
{
    mlock.Lock();
    std::vector<o3cw::CClient *>::iterator it=std::find(m_clients.begin(), m_clients.end(), &client);
    if (it!=m_clients.end())
        m_clients.erase(it);
    int result=m_clients.size();
    mlock.UnLock();
    UnUse();
    return result;
}
