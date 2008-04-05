// 
// File:   cuser.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 9:15
//

#ifndef _CUSER_H
#define	_CUSER_H

#include "types.h"

namespace o3cw
{
    class CUser
    {
    public:
        CUser();
        ~CUser();
        o3cw::ids GetUserId();
    private:
        o3cw::ids user_id;
    };
}


#endif	/* _CUSER_H */

