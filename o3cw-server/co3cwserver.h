// 
// File:   co3cwserver.h
// Author: alex
//
// Created on 20 Апрель 2008 г., 14:01
//

#ifndef _CO3CWSERVER_H
#define	_CO3CWSERVER_H

#include "../o3cw-lib/o3cw.h"

namespace o3cw
{
    class CO3CWBase;
    class CO3CWServer: o3cw::CO3CWBase
    {
    public:
        CO3CWServer();
        ~CO3CWServer();
        int Run();
        int LoadConfig(const char *config);
        int ExecCommand(o3cw::CCommand &cmd);
    private:
        o3cw::CCmdExec cmdexec1;
        o3cw::CCmdExec cmdexec2;
        o3cw::CCmdExec cmdexec3;
        o3cw::CConnectionHandler *connections_handler;
    };
}

#endif	/* _CO3CWSERVER_H */

