// 
// File:   co3cwserver.h
// Author: alex
//
// Created on 20 Апрель 2008 г., 14:01
//

#ifndef _CO3CWSERVER_H
#define	_CO3CWSERVER_H

#include "../o3cw-core/o3cw.h"
#include "cxmlconfig.h"

namespace o3cwapp
{
    class CMySQL;
    class CO3CWServer: o3cw::CO3CWBase
    {
    public:
        CO3CWServer();
        ~CO3CWServer();
        int Run();
        int Shutdown();
        int LoadConfig(const char *config);
        int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out);
    private:
        o3cw::CConnectionHandler *connections_handler;
        o3cw::CStorage store;
        o3cwapp::CXMLConfig config;
        o3cw::CUStorage<o3cw::CUser> users;
        o3cw::CUStorage<o3cw::CDoc> docs;
        o3cw::CCmdExec *cmdexec;
        o3cwapp::CMySQL *mysql;
        int threads_num;
        std::string admin_name;
    };
}

#endif	/* _CO3CWSERVER_H */

