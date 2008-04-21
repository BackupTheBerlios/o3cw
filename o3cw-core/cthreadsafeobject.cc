#include "cthreadsafeobject.h"

bonbon::CMutex o3cw::CThreadSafeObject::class_mlock;
bonbon::CSemaphore o3cw::CThreadSafeObject::class_slock;

o3cw::CThreadSafeObject::CThreadSafeObject()
{
    
}

o3cw::CThreadSafeObject::~CThreadSafeObject()
{
    
}
