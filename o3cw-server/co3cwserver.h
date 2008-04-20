// 
// File:   co3cwserver.h
// Author: alex
//
// Created on 20 Апрель 2008 г., 14:01
//

#ifndef _CO3CWSERVER_H
#define	_CO3CWSERVER_H

namespace o3cw
{
    class CO3CWBase;
    class CO3CWServer
    {
    public:
        CO3CWServer();
        ~CO3CWServer();
        int Run();
        int LoadConfig(const char *config);
    protected:
    };
}

#endif	/* _CO3CWSERVER_H */

