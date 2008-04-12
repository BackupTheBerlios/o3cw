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
#include "cclient.h"

namespace o3cw
{
    class CNetwork: public bonbon::CVThread
    {
    public:
        CNetwork();
        ~CNetwork();
    protected:
//        static bonbon::CJobManager<o3cw::CClient *> ;
    };
}

#endif	/* _CNETWORK_H */

