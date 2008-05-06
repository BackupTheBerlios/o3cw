#include "cthreadsafeobject.h"

bonbon::CMutex o3cw::CThreadSafeObject::class_mlock;
bonbon::CSemaphore o3cw::CThreadSafeObject::class_slock;

o3cw::CThreadSafeObject::CThreadSafeObject()
{
    m_use_count=0;
}

o3cw::CThreadSafeObject::~CThreadSafeObject()
{
    
}

int o3cw::CThreadSafeObject::Use()
{
    mlock.Lock();
    m_use_count++;
    mlock.UnLock();
    return 0;
}

int o3cw::CThreadSafeObject::UnUse()
{
    mlock.Lock();
    m_use_count--;
    mlock.UnLock();
    return 0;
}

int o3cw::CThreadSafeObject::GetUseCount()
{
    mlock.Lock();
    int result=m_use_count;
    mlock.UnLock();
    return result;
}

/*void o3cw::CThreadSafeObject::DeleteUnUsed()
{
    class_mlock.Lock();
    std::vector<o3cw::CThreadSafeObject *>::iterator it;
    for (it=delete_list.begin(); it<delete_list.end(); it++)
    {
        o3cw::CThreadSafeObject *obj=*it;
        if (obj!=NULL)
        {
            int use_count=obj->GetUseCount();
            if (use_count==0)
            {
                delete obj;
                delete_list.erase(it);
            }
            else if(use_count>0)
            {
                delete_list.erase(it);
            }
            else
            {
               printf(" * Error detected: use count<0\n"); 
            }
        }
    }
    class_mlock.UnLock();
}
*/
