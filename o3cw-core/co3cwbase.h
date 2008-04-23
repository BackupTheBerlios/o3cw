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
        ~CO3CWBase();
        static int LoadMainConfig(const char *filename);
        static int ReLoadMainConfig(const char *filename);
	static const o3cw::CConfig &GetMainConfig();
        static int PushCommand(o3cw::CCommand &cmd);
        virtual int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out);
    protected:
        static o3cw::CConfig o3cw_main_config;
        static o3cw::CO3CWBase *server;
        
    };
}

#endif	/* _CO3CWBASE_H */

