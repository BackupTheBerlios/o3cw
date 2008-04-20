// 
// File:   cnetwork.h
// Author: alex
//
// Created on 10 Апрель 2008 г., 13:19
//

#ifndef _CNETWORK_H
#define	_CNETWORK_H

#include <vector>

#include "libbonbon.h"
#include "co3cwbase.h"

namespace o3cw
{
    class CCommand;
    class CNetwork: public bonbon::CThread, public o3cw::CO3CWBase
    {
    public:
        CNetwork();
        ~CNetwork();
    protected:
        static bonbon::CJobManager<o3cw::CCommand *> cmd_bus;
    };
}

#endif	/* _CNETWORK_H */

