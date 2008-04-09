// 
// File:   csocket.h
// Author: alex
//
// Created on 9 Апрель 2008 г., 16:16
//

#ifndef _CSOCKET_H
#define	_CSOCKET_H
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "libbonbon.h"

#define CRS_ERR_BIND 1
#define CRS_ERR_LISTEN 2
#define CRS_ERR_ACCEPT 3
#define CRS_ERR_CONNECT 4
#define CRS_ERR_LOST 5
#define CRS_ERR_SEND 6
#define CRS_ERR_SEQ 7

namespace o3cw
{
    class CSocket: public bonbon::CJob
    {
    public:
        CSocket();
        CSocket(int sock_id);
        ~CSocket();
        int Bind(int port, const char *i);
        int Listen();
        int Accept();
        int Send(const char *message);
        int Send(const char *message, size_t size);
        int Send(std::string &message);
        int Receive(std::string &buff, int max_size);
        int Receive(std::string &buff, int max_size, float timeout);
        void ForceDown();
        int GetFD();
        static int readmultiselect(std::queue<o3cw::CSocket *> &int_s_list, std::queue<o3cw::CSocket *> &out_s_list, int sec, int usec);
    private:
        int socket_id;
        int listener;
        sockaddr_in addr;
        sem_t read_lock;
        fd_set rfds;
        fd_set wfds;
        struct timeval rtv;
        struct timeval wtv;
        int error;
        bonbon::CMutex lock;
        std::string int_buff;

    };
}

#endif	/* _CSOCKET_H */

