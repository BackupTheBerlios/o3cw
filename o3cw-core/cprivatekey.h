// 
// File:   cprivatekey.h
// Author: alex
//
// Created on 13 Май 2008 г., 0:46
//

#ifndef _CPRIVATEKEY_H
#define	_CPRIVATEKEY_H

#include "ckey.h"

namespace o3cw
{
    class CKey;
    
    /* Abstract class for private cryptography keys */
    class CPrivateKey: public o3cw::CKey
    {
    public:
        CPrivateKey();
        virtual ~CPrivateKey();
    };
}


#endif	/* _CPRIVATEKEY_H */

