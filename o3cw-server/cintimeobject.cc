#include <time.h>

#include "cintimeobject.h"

o3cw::CInTimeObject::CInTimeObject()
{
    GetTime(creation_time);
}

o3cw::CInTimeObject::~CInTimeObject()
{
    
}

long long o3cw::CInTimeObject::GetCreationTime()
{
    return creation_time;
}

void o3cw::CInTimeObject::GetTime(long long &buff)
{
    time_t tnow;
    time(&tnow);
    memset(&buff, 0, sizeof(buff));
    memcpy(&buff, &tnow, sizeof(tnow));
}
