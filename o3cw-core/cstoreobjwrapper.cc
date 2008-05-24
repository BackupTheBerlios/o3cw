#include <assert.h>

#include "cstoreobjwrapper.h"
#include "cuser.h"
#include "cdoc.h"

o3cw::CStoreObjWrapper::CStoreObjWrapper(const char *type)
{
    assert(type!=0);
    
    if (strcmp(type, "user")==0)
        pattern=new o3cw::CUser();
    else if (strcmp(type, "doc")==0)
        pattern=new o3cw::CDoc();

    assert(pattern!=0);
}

o3cw::CStoreObjWrapper::~CStoreObjWrapper()
{
    if (pattern!=0)
        delete pattern;
}

int o3cw::CStoreObjWrapper::Open(o3cw::CCommand &cmd, o3cw::CCommand &out, o3cw::CIdsObject **element)
{
    return pattern->Open(cmd, out, element);
}
