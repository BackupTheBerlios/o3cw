// 
// File:   cintimeobject.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 10:40
//

#ifndef _CINTIMEOBJECT_H
#define	_CINTIMEOBJECT_H

#include "types.h"
#include "cidsobject.h"

namespace o3cw
{
    class CInTimeObject: public o3cw::CIdsObject
    {
    public:
        CInTimeObject();
        ~CInTimeObject();
        o3cw::time GetCreationTime();
    private:
        o3cw::time creation_time;
    };
}


#endif	/* _CINTIMEOBJECT_H */

