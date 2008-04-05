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
#include "cintimeobject.h"

namespace o3cw
{
    class CShareObject: public o3cw::CInTimeObject
    {
    public:
        CShareObject();
        ~CShareObject();
        bool UserCanWrite(o3cw::ids user_id);
        bool UserCanRead(o3cw::ids user_id);
        int SetPermissions(o3cw::CPermission &perm);
    private:
        o3cw::CPermission obj_perm;
    };
}

#endif	/* _CSHAREDOBJECT_H */

