// 
// File:   cacessmode.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 9:28
//

#ifndef _CACESSMODE_H
#define	_CACESSMODE_H

#include "types.h"
#include "libbonbon.h"
#include "cthreadsafeobject.h"
namespace o3cw
{
    class CAcessMode: public o3cw::CThreadSafeObject
    {
    public:
        CAcessMode();
        CAcessMode(o3cw::ids user_id, bool allow_read, bool allow_write);
        virtual ~CAcessMode();
        o3cw::ids GetUserId();
        bool ReadAllowed();
        bool WriteAllowed();
        bool operator==(const o3cw::CAcessMode &m);
        o3cw::CAcessMode &operator=(const o3cw::CAcessMode &m);
    private:
        o3cw::ids user;
        bool r;
        bool w;
    };
}

#endif	/* _CACESSMODE_H */

