// 
// File:   cthreadsafeobject.h
// Author: alex
//
// Created on 8 Апрель 2008 г., 20:59
//

#ifndef _CTHREADSAFEOBJECT_H
#define	_CTHREADSAFEOBJECT_H

#include "libbonbon.h"

namespace o3cw
{
    class CThreadSafeObject
    {
    public:
        CThreadSafeObject();
        virtual ~CThreadSafeObject();
        bonbon::CMutex mlock;
        bonbon::CSemaphore slock;
        
        static bonbon::CMutex class_mlock;
        static bonbon::CSemaphore class_slock;
    };
}

#endif	/* _CTHREADSAFEOBJECT_H */

