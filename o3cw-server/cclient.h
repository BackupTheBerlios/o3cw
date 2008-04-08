// 
// File:   cclient.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 0:04
//

#ifndef _CCLIENT_H
#define	_CCLIENT_H

namespace o3cw
{
    class CUser;
    
    class CClient
    {
    public:
        CClient();
        ~CClient();
    private:
        CUser *user;
        bool trusted;
    };
}

#endif	/* _CCLIENT_H */

