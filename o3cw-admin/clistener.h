// 
// File:   clistener.h
// Author: alex
//
// Created on 23 Апрель 2008 г., 23:44
//

#ifndef _CLISTENER_H
#define	_CLISTENER_H

#include "../o3cw-core/o3cw.h"

namespace adm
{
    class CListener: public bonbon::CThread
    {
    public:
        CListener(o3cw::CClient *cl);
        ~CListener();
        int ThreadExecute();
    private:
        o3cw::CClient *client;
    };
}
#endif	/* _CLISTENER_H */

