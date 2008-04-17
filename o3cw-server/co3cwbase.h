// 
// File:   co3cwbase.h
// Author: alex
//
// Created on 7 Апрель 2008 г., 18:26
//

#ifndef _CO3CWBASE_H
#define	_CO3CWBASE_H

#include "cconfig.h"
#include "cintimeobject.h"

namespace o3cw
{
    class CO3CWBase: public o3cw::CInTimeObject
    {
    public:
        CO3CWBase();
        ~CO3CWBase();
        static int LoadMainConfig(const char *filename);
        static int ReLoadMainConfig(const char *filename);
	static const o3cw::CConfig &GetMainConfig();
    protected:
        static o3cw::CConfig o3cw_main_config;
        
    };
}

#endif	/* _CO3CWBASE_H */

