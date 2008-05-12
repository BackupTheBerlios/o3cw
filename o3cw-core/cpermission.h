// 
// File:   cpermission.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 9:19
//

#ifndef _CPERMISSION_H
#define	_CPERMISSION_H

#include <vector>

#include "cacessmode.h"
#include "types.h"
#include "cthreadsafeobject.h"

namespace o3cw
{
    class CConfig;
    class CPermission: public o3cw::CThreadSafeObject
    {
    public:
        CPermission();
        virtual ~CPermission();
        int Set (o3cw::ids user_id, bool read, bool write);
        bool UserCanWrite(o3cw::ids user_id);
        bool UserCanRead(o3cw::ids user_id);
    private:
        std::vector<o3cw::CAcessMode> modes;
    };
}


#endif	/* _CPERMISSION_H */

