// 
// File:   co3cwbase.h
// Author: alex
//
// Created on 7 Апрель 2008 г., 18:26
//

#ifndef _CO3CWBASE_H
#define	_CO3CWBASE_H

#include "cintimeobject.h"

namespace o3cw
{
    class CCommand;
    class CConfig;
    class CO3CWBase: public o3cw::CInTimeObject
    {
    public:
        CO3CWBase();
        virtual ~CO3CWBase();
        
        /* Setup main o3cw config (usually located at /etc/o3cw-server.cfg) */
        static int SetMainConfig(o3cw::CConfig &config);
        
        /* Reload main config */
        static int ReLoadMainConfig(const char *filename);
        
        /* Get main config */
	static const o3cw::CConfig &GetMainConfig();
        
        /* Push command sequence */
        static int PushCommand(o3cw::CCommand &cmd);
        
        /* Execute command sequence */
        virtual int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out);
        
        static int StaticExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out);
    protected:
        static o3cw::CConfig *o3cw_main_config;
        static o3cw::CO3CWBase *server;
        
    };
}

#endif	/* _CO3CWBASE_H */

