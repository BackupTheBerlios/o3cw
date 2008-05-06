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
        
        /* Execute "open" command. If *element is NULL, that means that requested element does not
         * exists in store.
         * Open() can create new element (using "new" operator), initialize it
         * set *element pointer to created element and return 0,
         * OR
         * return non-zero error code and keep *element as NULL.
         * If *element is not NULL, that means that that requested element exists in store already,
         * and Open() needs just to return zero if client can open it or error code otherwise.
         */
        static int Open(o3cw::CCommand &cmd, o3cw::CCommand &out, o3cw::CO3CWBase **element);
        
        static int StaticExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out);
    protected:
        static o3cw::CConfig *o3cw_main_config;
        static o3cw::CO3CWBase *server;
        
    };
}

#endif	/* _CO3CWBASE_H */

