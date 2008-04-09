// 
// File:   cconnectionhandler.h
// Author: alex
//std::vector <paycheck::CSocket *> *connections_store;
// Created on 9 Апрель 2008 г., 16:31
//

#ifndef _CCONNECTIONHANDLER_H
#define	_CCONNECTIONHANDLER_H

#include <queue>

#include "libbonbon.h"
#include "csocket.h"

namespace o3cw
{
    class CConnectionHandler
    {
    public:
        CConnectionHandler();
        ~CConnectionHandler();
        int Execute();
        void Kill();
        bool Killed();
    private:
        bonbon::CMutex kill_lock;
        bool killed;
        static bonbon::CMutex connections_lock;
        static o3cw::CSocket *listener;
        std::queue <o3cw::CSocket *> connections_store;
    };
}

#endif	/* _CCONNECTIONHANDLER_H */
