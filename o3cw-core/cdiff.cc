#include "cdiff.h"
#include "cdoc.h"
#include "cdocpart.h"
#include "ccommand.h"
#include "cclient.h"
#include "cuser.h"
#include "error.h"

o3cw::CUniqueAux o3cw::CDiff::diff_uaux;

o3cw::CDiff::CDiff(const std::string &data, const o3cw::CHash &key, o3cw::CDifferenced &prnt): o3cw::CDifferenced(prnt, diff_uaux), m_parent(prnt)
{
    m_diff_data=data;
    m_diff_data_hash=key;
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
            ConfirmBy(*user);
        }
        else if (c1=="reject")
        {
            RejectBy(*user);
        }
        else if (c1=="recall")
        {
            /* Recall by a diff creator */
            RecallBy(*user);

        }
        else if (c1=="accept")
        {
           AcceptBy(*user);
        }
    }
    
    return result;
}

int o3cw::CDiff::RemoveClientFromMulticast(const o3cw::CClient &client)
{
    mlock.Lock();
    m_accepted=RefreshAccept();
    mlock.UnLock();
    return 0;
}

bool o3cw::CDiff::CheckAccepted()
{
    if (m_accepted)
	return true;
    bool result=false;

    /* Idea is a bit ugly, but code is very simple */
    std::vector<o3cw::CClient *> clients_connected=GetClientsConnected();
    std::vector<o3cw::CClient *>::iterator client_it;
    std::vector<o3cw::CUser *>::iterator user_it;
    for (client_it=clients_connected.begin(); client_it<clients_connected.end(); client_it++)
    {
	for (user_it=m_confirmed_by.begin(); user_it<m_confirmed_by.end(); user_it++)
	{
	    if ((*user_it)==(*client_it)->GetUser())
	    {
		client_it=--clients_connected.erase(client_it);
	    }
	}
    }

    
    if (clients_connected.size()==0)
    {
	/* All users confirmed this diff */
	result=true;
    }
    return result;
}

bool o3cw::CDiff::RefreshAccept()
{
    if (m_accepted)
	return false;
	
    if ((m_accepted=CheckAccepted())==true)
    {
	/* Diff accepted! */
	o3cw::CCommand cmd;
	cmd.Push("diff");
	cmd.Push("accepted");
	//m_parent.MultiCast(cmd);
	return true;
    }
    return false;
}

int o3cw::CDiff::ConfirmBy(o3cw::CUser &user)
{
    int result=0;
    if (m_accepted)
    {
        /* Can't confirm - already accepted */
    }
    else
    {
        /* Confirm diff */
        bool already_confirmed=false;
        std::vector<o3cw::CUser *>::iterator it;

        mlock.Lock();
        for (it=m_confirmed_by.begin(); it<m_confirmed_by.end() && !already_confirmed; it++)
        {
            if ((*it)==&user)
                already_confirmed=true;
        }

        if (already_confirmed==false)
        {
            user.Use();
            m_confirmed_by.push_back(&user);
        }

        /* Checking if everyone confirmed (do accept) */
        m_accepted=CheckAccepted();
        mlock.UnLock();
    }
    return result;
}

int o3cw::CDiff::RejectBy(o3cw::CUser &user)
{
    /* Reject diff */
    
    int result=0;
    std::vector<o3cw::CUser *>::iterator it;
    mlock.Lock();
    for (it=m_confirmed_by.begin(); it<m_confirmed_by.end(); it++)
    {
        if ((*it)==&user)
        {
            user.UnUse();
            it=--m_confirmed_by.erase(it);
            break;
        }
    }
    mlock.UnLock();
    return result;
}

int o3cw::CDiff::RecallBy(o3cw::CUser &user)
{
    return 0;
}

int o3cw::CDiff::AcceptBy(o3cw::CUser &user)
{
     /* Force accept */
    mlock.Lock();
    m_accepted=true;
    mlock.UnLock();
    return 0;
}
