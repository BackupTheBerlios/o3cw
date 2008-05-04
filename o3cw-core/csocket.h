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
#include "cintimeobject.h"

#define CRS_ERR_BIND 1
#define CRS_ERR_LISTEN 2
#define CRS_ERR_ACCEPT 3
#define CRS_ERR_CONNECT 4
#define CRS_ERR_LOST 5
#define CRS_ERR_SEND 6
#define CRS_ERR_SEQ 7

namespace o3cw
{
    class CSocket: public o3cw::CInTimeObject
    {
    public:
        CSocket();
        /* Create new sock, associated with specified socket */
        CSocket(int sock_id);
        
        virtual ~CSocket();
        
        /* Bind socket to a port */
        int Bind(int port, const char *i);
        
        /* Switch to a listening mode (after bind) */
        int Listen();
        
        /* Accept new conection. Attention - it can blocks. Call readmultiselect first */
        int Accept();
        
        /* Connect to a specified ip. Return socket id on sucess, -1 on failure  */
        int Connect(const char *ip, int port);
        
        /*
         * Send a simply message. Message must be a 0-terminated string
         * Returns 0 on sucess
         */
        int Send(const char *message);
        
        /*
         * Send message 
         * Returns 0 on sucess
         */
        int Send(const char *message, size_t size);
        int Send(std::string &message);
    
        /*
         * Receive data and copy them to buff
         * Returns amount of data, or negativ value on error
         * Attention - it can blocks. Call readmultiselect first 
         */
        int Receive(std::string &buff);
        
        /*
         * Receive data and copy them to buff
         * Returns amount of data, or negativ value on error
         * If no data received in "timeout" sec - 0 returned.
         */        
        int Receive(std::string &buff, float timeout);
        
        /* Shutdown socket and close it */
        void ForceDown();
        
        /* Get number of sec passed after last incoming activity on socket */
        int ConnectionTimeout();
        
        /* Returns socket file descriptor or -1 if it's not specified */
        int GetFD();
        
        /*
         * Gets sockets from in_s_list and pushes
         * sockets with new data aviable for reading to out_s_list (or with lost connection).
         * Waits sec seconds and usec miliseconds for new data.
         * After executions, in_s_list contatins socket without new data
         * out_s_list - sockets with a new data.
         * Returns number of sockets added to out_s_list
         */
        static int readmultiselect(std::queue<o3cw::CSocket *> &in_s_list, std::queue<o3cw::CSocket *> &out_s_list, int sec, int usec);
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
        std::string int_buff;
        long long last_activity_time;
    };
}

#endif	/* _CSOCKET_H */

