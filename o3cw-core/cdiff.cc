#include "cdiff.h"
#include "cdocpart.h"
#include "ccommand.h"
#include "cclient.h"
#include "cuser.h"
#include "error.h"

o3cw::CUniqueAux o3cw::CDiff::diff_uaux;

o3cw::CDiff::CDiff(std::string &data, std::string &data_hash, o3cw::CDocPart &docpart): o3cw::CIdsObject(diff_uaux), m_diff_data_hash(data_hash), m_parent_docpart(docpart)
{
    m_diff_data=data;
}

o3cw::CDiff::~CDiff()
{
    
}

int o3cw::CDiff::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out)
{
    int result=0;
    o3cw::CUser *user=cmd.GetClient().GetUser();
    
    /* Permission denied */
    if (user==NULL)
        return O3CW_ERR_DENIED;
    
    if (cmd.CmdAviable())
    {
        std::string &c1=cmd.Pop();
        if (c1=="confirm")
        {
            /* Confirm diff */
            bool already_confirmed=false;
            std::vector<o3cw::CUser *>::iterator it;
            
            mlock.Lock();
            for (it=m_confirmed_by.begin(); it<m_confirmed_by.end() && !already_confirmed; it++)
            {
                if ((*it)==user)
                    already_confirmed=true;
            }
            
            if (already_confirmed==false)
            {
                user->Use();
                m_confirmed_by.push_back(user);
            }
            mlock.UnLock();
        }
        else if (c1=="reject")
        {
            /* Reject diff */
            std::vector<o3cw::CUser *>::iterator it;
            mlock.Lock();
            for (it=m_confirmed_by.begin(); it<m_confirmed_by.end(); it++)
            {
                if ((*it)==user)
                {
                    user->UnUse();
                    m_confirmed_by.erase(it);
                    break;
                }
            }
            mlock.UnLock();
        }
        else if (c1=="recall")
        {
            /* Recall by a diff creator */

        }
        else if (c1=="accept")
        {
            /* Force accept */
            mlock.Lock();
            m_accepted=true;
            mlock.UnLock();
        }
    }
    
    return result;
}
