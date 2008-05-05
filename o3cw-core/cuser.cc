#include "cuser.h"
#include "cclient.h"
#include "ccommand.h"
#include "ccmdexec.h"
#include "csql.h"
#include "cconfig.h"

o3cw::CUniqueAux o3cw::CUser::unique_data;

o3cw::CUser::CUser(): o3cw::CIdsObject::CIdsObject(unique_data)
{
    
}

o3cw::CUser::~CUser()
{
    
}

void o3cw::CUser::GetName(std::string &buff)
{
    mlock.Lock();
    buff=name;
    mlock.UnLock();
}

int o3cw::CUser::StaticExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out)
{
    int result=-1;
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
                        }
                    }
                    else
                    {
                        std::string request("select password from users where name='");
                        request+=c2;
                        request+="'";
                        cmd.GetExecutor().SQL().SQLRequest(request);
                        std::vector <std::string> sql_result;
                        if (cmd.GetExecutor().SQL().GetNextDataSet(sql_result)==0)
                        {
                            std::string &c3=cmd.Pop();
                            if (c3==sql_result[0])
                            {
                                printf("Access granted\n");
                                result=0;
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
                        printf("Access granted. Hello, admin\n");
                        result=0;
                    }
                }
                cmd.Back();
            }
        }
        cmd.Back();
    }
    
    return result;
}

int o3cw::CUser::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out)
{
    if (cmd.CmdAviable())
    {
        std::string &c1=cmd.Pop();
        printf("c1=%s\n", c1.c_str());
        if (c1=="open")
        {
            cmd.GetClient().SetUser(*this);
        }
        
        if (cmd.CmdAviable())
        {
            std::string &c2=cmd.Pop();
            mlock.Lock();
            name=c2;
            mlock.UnLock();
        }
    }
    return 0;
}
