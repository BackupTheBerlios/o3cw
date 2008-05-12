// 
// File:   cpublickey.h
// Author: alex
//
// Created on 13 Май 2008 г., 0:45
//

#ifndef _CPUBLICKEY_H
#define	_CPUBLICKEY_H

#include "ckey.h"

namespace o3cw
{
    class CKey;
    
    /* Abstract class for public cryptography keys */
    class CPublicKey: public o3cw::CKey
    {
    public:
        CPublicKey();
        virtual ~CPublicKey();
    };
}

#endif	/* _CPUBLICKEY_H */

