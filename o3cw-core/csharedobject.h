// 
// File:   csharedobject.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 9:36
//

#ifndef _CSHAREDOBJECT_H
#define	_CSHAREDOBJECT_H

#include "types.h"
#include "cpermission.h"
#include "co3cwbase.h"
#include "libbonbon.h"

namespace o3cw
{
    class CSharedObject: public o3cw::CO3CWBase
    {
    public:
        CSharedObject();
        virtual ~CSharedObject();
        bool UserCanWrite(o3cw::ids user_id);
        bool UserCanRead(o3cw::ids user_id);
        int SetPermissions(o3cw::CPermission &perm);
    private:
        o3cw::CPermission obj_perm;
    };
}

#endif	/* _CSHAREDOBJECT_H */

