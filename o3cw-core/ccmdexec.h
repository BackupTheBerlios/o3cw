// 
// File:   ccmdexec.h
// Author: alex
//
// Created on 20 Апрель 2008 г., 10:39
//

#ifndef _CCMDEXEC_H
#define	_CCMDEXEC_H

#include "cnetwork.h"

namespace o3cw
{
    class CCmdExec: public o3cw::CNetwork
    {
    public:
        CCmdExec();
        virtual ~CCmdExec();
        int ThreadExecute();
    };
}

#endif	/* _CCMDEXEC_H */

