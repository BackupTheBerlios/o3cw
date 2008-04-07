// 
// File:   cidsobject.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 12:13
//

#ifndef _CIDSOBJECT_H
#define	_CIDSOBJECT_H

#include "types.h"
#include "co3cwbase.h"

namespace o3cw
{
    class CIdsObject: public o3cw::CO3CWBase
    {
    public:
        CIdsObject();
        ~CIdsObject();
        o3cw::ids GetId();
    protected:
        o3cw::ids id;
    };
}


#endif	/* _CIDSOBJECT_H */

