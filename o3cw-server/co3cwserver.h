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
#include "cmysql.h"

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
    
	/* Main o3cw config */
        o3cwapp::CXMLConfig config;


	/* Storage */
        o3cw::CStorage users;
        o3cw::CStorage docs;
	
	/* Command executors (threads) */
        o3cw::CCmdExec *cmdexec;
	
	/* Connection handlers */
	o3cw::CConnectionHandler *connections_handler;
	
	/* Mysql connections */
        o3cwapp::CMySQL *mysql;
	
	/* Threads amount */
        int threads_num;
	
	/* Admin name (login) */
        std::string admin_name;
    };
}

#endif	/* _CO3CWSERVER_H */

