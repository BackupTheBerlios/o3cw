#include "cdifferenced.h"
#include "cuser.h"
#include "cdiff.h"
#include "error.h"

o3cw::CDifferenced::CDifferenced(o3cw::CDifferenced &prnt, o3cw::CUniqueAux &daux): o3cw::CIdsObject::CIdsObject(daux), m_parent(prnt)
{
    
}

o3cw::CDifferenced::~CDifferenced()
{
    
}

int o3cw::CDifferenced::AddDiff(const std::string &diff_content, const o3cw::CHash &diff_hash, o3cw::CUser &user)
{
    int result=0;
    if (diff_content.length()>0)
    {
        
        bool already_exists=false;
        std::vector<o3cw::CDiff *>::iterator search_it;
        
        mlock.Lock();
         
        for (search_it=m_diffs.begin(); !already_exists && search_it<m_diffs.end(); search_it++)
        {
            o3cw::CDiff *diff=*search_it;
            if (diff!=NULL && diff->GetKey()==diff_hash)
                already_exists=true;
        }

        if (already_exists)
        {
            /* Error - this diff alreay commited */
            result=O3CW_ERR_DUBLICATE;
        }
        else
        {
            /* Add new diff */
            o3cw::CDiff *new_diff=new o3cw::CDiff(diff_content, diff_hash, *this);

            if (new_diff!=NULL)
                m_diffs.push_back(new_diff);
            else
                result=O3CW_ERR_OUT_OF_MEM;
        }
        mlock.UnLock();
    }
    else
        result=O3CW_ERR_DATA_EMPTY;
    return result;
}

o3cw::CDiff *o3cw::CDifferenced::FindDiff(const o3cw::CHash &diff_hash)
{
    o3cw::CDiff *result=NULL;
    std::vector<o3cw::CDiff *>::iterator search_it;

    for (search_it=m_diffs.begin(); result==NULL && search_it<m_diffs.end(); search_it++)
    {
        o3cw::CDiff *diff=*search_it;
        if (diff!=NULL && diff->GetKey()==diff_hash)
            result=diff;
    }
    return result;
}

int o3cw::CDifferenced::ConfirmDiff(o3cw::CHash &diff_hash, o3cw::CUser &user)
{
    int result=0;
    
    mlock.Lock();
    o3cw::CDiff *diff=NULL;
    if ((diff=FindDiff(diff_hash))!=NULL)
        result=diff->ConfirmBy(user);
    else
        result=O3CW_ERR_NOT_FOUND;
    mlock.UnLock();
    
    return result;
}

int o3cw::CDifferenced::RejectDiff(o3cw::CHash &diff_hash, o3cw::CUser &user)
{    
    int result=0;
    
    mlock.Lock();
    o3cw::CDiff *diff=NULL;
    if ((diff=FindDiff(diff_hash))!=NULL)
        result=diff->RejectBy(user);
    else
        result=O3CW_ERR_NOT_FOUND;
    mlock.UnLock();
    
    return result;
}

int o3cw::CDifferenced::RecallDiff(o3cw::CHash &diff_hash, o3cw::CUser &user)
{
    int result=0;
    
    mlock.Lock();
    o3cw::CDiff *diff=NULL;
    if ((diff=FindDiff(diff_hash))!=NULL)
        result=diff->RecallBy(user);
    else
        result=O3CW_ERR_NOT_FOUND;
    mlock.UnLock();
    return result;
}

int o3cw::CDifferenced::AcceptDiff(o3cw::CHash &diff_hash, o3cw::CUser &user)
{
    int result=0;
    
    mlock.Lock();
    o3cw::CDiff *diff=NULL;
    if ((diff=FindDiff(diff_hash))!=NULL)
        result=diff->AcceptBy(user);
    else
        result=O3CW_ERR_NOT_FOUND;
    mlock.UnLock();
    return result;
}
