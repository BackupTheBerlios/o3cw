#include "cacessmode.h"

o3cw::CAcessMode::CAcessMode(): o3cw::CThreadSafeObject::CThreadSafeObject()
{
    r=false;
    w=false;
}

o3cw::CAcessMode::~CAcessMode()
{
    
}

bool o3cw::CAcessMode::ReadAllowed()
{
    return r;
}

bool o3cw::CAcessMode::WriteAllowed()
{
    return w;
}

bool o3cw::CAcessMode::operator==(const o3cw::CAcessMode &m)
{
    bool result=false;
    mlock.Lock();
    if (r==m.r && w==m.w)
        result=true;
    mlock.UnLock();
    return result;
}

o3cw::CAcessMode &o3cw::CAcessMode::operator=(const o3cw::CAcessMode &m)
{
    class_mlock.Lock();
    r=m.r;
    r=m.w;
    class_mlock.UnLock();
    return *this;
}
