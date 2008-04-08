// 
// File:   cintimeobject.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 10:40
//

#ifndef _CINTIMEOBJECT_H
#define	_CINTIMEOBJECT_H

#include "types.h"
#include "cthreadsafeobject.h"

namespace o3cw
{
    class CInTimeObject: public o3cw::CThreadSafeObject
    {
    public:
        CInTimeObject();
        ~CInTimeObject();
        long long GetCreationTime();
        void GetTime(long long &buff);
    private:
        long long creation_time;
    };
}


#endif	/* _CINTIMEOBJECT_H */

