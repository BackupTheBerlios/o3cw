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
#include "cclient.h"
#include "cnetwork.h"

namespace o3cw
{
    class CConnectionHandler: public o3cw::CNetwork
    {
    public:
        CConnectionHandler();
        virtual ~CConnectionHandler();
        int ThreadExecute();
    private:
        static bonbon::CMutex connections_lock;
        static o3cw::CClient *listener;
        std::vector <o3cw::CClient *> connections_store;
        std::queue <o3cw::CClient *> to_delete;
        int max_fd;
        fd_set socket_set;
    };
}

#endif	/* _CCONNECTIONHANDLER_H */
