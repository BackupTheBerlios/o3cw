// 
// File:   cclient.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 0:04
//

#ifndef _CCLIENT_H
#define	_CCLIENT_H

#include "csocket.h"

namespace o3cw
{
    class CUser;
    
    class CClient: public o3cw::CSocket
    {
    public:
        CClient();
        CClient(int sock);
        ~CClient();
        static int readmultiselect(std::queue<o3cw::CClient *> &in_s_list, std::queue<o3cw::CClient *> &out_s_list, int sec, int usec);
        int Receive();
    private:
        o3cw::CUser *user;
        o3cw::CSocket *socket;
        bool trusted;
        std::string msgbuff;
        std::string head;
        std::string body;
        int message_left;
        size_t head_starts;
        size_t head_ends;
    };
}

#endif	/* _CCLIENT_H */

