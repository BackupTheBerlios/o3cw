#include "cidsobject.h"

std::vector<o3cw::CIdsObject *> o3cw::CIdsObject::delete_list;

o3cw::CIdsObject::CIdsObject(o3cw::CUniqueAux &aux): o3cw::CSharedObject::CSharedObject()
{
    /* Generetaing new ID for this object */
    idlist=&(aux.id_list);
    idlock=&(aux.id_lock);
    GenerateNewId(aux.id_lock, aux.current_id, aux.id_list);
    m_use_count=0;
}

o3cw::CIdsObject::~CIdsObject()
{
    FreeMyId(*idlock, *idlist);
}

o3cw::ids o3cw::CIdsObject::GetId() const
{
    return obj_id;
}

void o3cw::CIdsObject::FreeMyId(bonbon::CMutex &id_lock, std::list<o3cw::ids *> &id_list)
{
    bool deleted=false;
    o3cw::ids counter=0;
    id_lock.Lock();
        
    std::list<o3cw::ids *>::iterator it;
    for (it=id_list.begin(); counter<=obj_id && !deleted && it!=id_list.end(); counter++)
    {
        if (**it==obj_id)
        {
            id_list.erase(it);
            deleted=true;
        }
        else
            it++;
    }
    if (deleted==false)
    {
        /* Strange - looks like I didnt find my id in list */
        printf("Can't delete id from list. Are you sure you didn't touch it by dirty hands?\n");
    }
    id_lock.UnLock();
    return;
}

bool o3cw::CIdsObject::operator <(const CIdsObject &comp)
{
    if (comp.obj_id>obj_id)
        return true;
    return false;
}

void o3cw::CIdsObject::GenerateNewId(bonbon::CMutex &id_lock, o3cw::ids &current_id, std::list<o3cw::ids *> &id_list)
{
    bool id_free=false;
    bool reset_once=false;
    bool counter_inc=true;
    id_lock.Lock();
        
    std::list<o3cw::ids *>::iterator it;
    o3cw::ids counter=0;
    for (it=id_list.begin();counter<=current_id && !id_free && it!=id_list.end();)
    {
        if(**it==current_id)
        {
            if (current_id<O3CW_MAX_IDS_VALUE)
            {
                //printf("**it==current_id! ++\n");
                current_id++;
                it++;
            }
            else
            {
                //printf("**it==current_id! RESET\n");
                if (reset_once)
                {
                    //printf("FATAL: can't find free id\n");
                    exit(-1);
                }
                else
                {
                    /* Max val reached - start from begining */
                    current_id=0;
                    counter=0;
                    it=id_list.begin();
                    reset_once=true;
                    
                    /* Dont increase counter on this step */
                    counter_inc=false;

                }
                
            }
        }
        else if (**it>current_id)
        {
            printf("**it=%u > current_id=%u\n",**it, current_id);
            id_free=true;
        }
        else
        {
            printf("it++\n");
            it++;
        }
        if (counter_inc)
            counter++;
        else
            counter_inc=true;
    }

    /* Assign new ID */
    obj_id=current_id;
    
    /* Write new ID to list of occuped IDs */
    id_list.insert(it, &obj_id);
    
    id_lock.UnLock();
    
    return;
}

int o3cw::CIdsObject::SetKey(o3cw::CHash &new_key)
{
    mlock.Lock();
    m_key=new_key;
    mlock.UnLock();
    return 0;
}

const o3cw::CHash &o3cw::CIdsObject::GetKey() const
{
    return m_key;
}

int o3cw::CIdsObject::Use()
{
    mlock.Lock();
    m_use_count++;
    mlock.UnLock();
    return 0;
}

int o3cw::CIdsObject::UnUse()
{
    mlock.Lock();
    m_use_count--;
    if (m_use_count==0)
    {
        class_mlock.Lock();
        delete_list.push_back(this);
        class_mlock.UnLock();
    }
    mlock.UnLock();
    return 0;
}

int o3cw::CIdsObject::GetUseCount()
{
    mlock.Lock();
    int result=m_use_count;
    mlock.UnLock();
    return result;
}

int o3cw::CIdsObject::Open(o3cw::CCommand &cmd, o3cw::CCommand &out, o3cw::CIdsObject **e)
{
    return 0;
}
