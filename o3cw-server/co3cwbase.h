// 
// File:   co3cwbase.h
// Author: alex
//
// Created on 7 Апрель 2008 г., 18:26
//

#ifndef _CO3CWBASE_H
#define	_CO3CWBASE_H

#include "cconfig.h"

namespace o3cw
{
    class CO3CWBase
    {
    public:
        CO3CWBase();
        ~CO3CWBase();
        int LoadConfig(const char *filename);
        int ReLoadConfig(const char *filename);
    protected:
        static o3cw::CConfig o3cw_main_config;
        
    };
}

#endif	/* _CO3CWBASE_H */

