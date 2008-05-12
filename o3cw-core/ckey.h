// 
// File:   ckey.h
// Author: alex
//
// Created on 13 Май 2008 г., 0:44
//

#ifndef _CKEY_H
#define	_CKEY_H

namespace o3cw
{
    /* Abstract class for cryptography keys */
    class CKey
    {
    public:
        CKey();
        virtual ~CKey();
    };
}

#endif	/* _CKEY_H */

