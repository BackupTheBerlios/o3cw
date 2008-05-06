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
    class CDoc;
    class CClient: public o3cw::CSocket
    {
    public:
        CClient();
        
        /* Create new client, associated with socket */
        CClient(int sock);
        virtual ~CClient();
        
        /* See readmultiselect in CSocket class (csocket.cc) */
        static int FdSetCompile(fd_set &read_fds, std::vector<o3cw::CClient *> &in_list);
        static int FdGetMax(std::vector<o3cw::CClient *> &in_list);
        static int FdSetRemove(fd_set &read_fds, int &max_fd, std::vector<o3cw::CClient *> &in_list, o3cw::CClient &client);
        static int FdSetAdd(fd_set &read_fds, int &max_fd, std::vector<o3cw::CClient *> &in_list, o3cw::CClient &client);
        static int readmultiselect(fd_set &read_fds, int &max_fd, std::vector<o3cw::CClient *> &in_list, std::queue<std::vector <o3cw::CClient *>::iterator> &out_list, int sec, int usec);
        /*
         * Receive new message from sock
         * 0 - no new message received
         * 1 - new message aviable (get by GetHead and GetBody)
         *-1 - error on socket (connection lost)
         */
        int Receive();
        int Receive(float timeout);
        
        /* Copy head to buff. Returns 1 on sucess, 0 if there is no new head */
        std::string *GetHead();
        
        /* Copy body to buff. Returns 1 on sucess, 0 if there is no new body */
        std::string *GetBody();
        
        /* Return true if client is authoriuzed, trusted, "good" client */
        bool Trusted();
	
	int SendGenericError(int error);
        
        int SendBody(std::string &data);
        
        int OpenDoc(o3cw::CDoc &doc);
        int CloseDoc(o3cw::CDoc &doc);
        
        int SetUser(o3cw::CUser &user);
        o3cw::CUser *GetUser();
    private:
        std::string *GetStringFromQueue(std::queue<std::string *> &queue);
        o3cw::CUser *m_user;
        o3cw::CSocket *socket;
        bool trusted;
        std::string msgbuff;
        
        std::queue<std::string *> heads;
        std::queue<std::string *> bodies;
        std::string body;
        std::string head;
        int message_left;
        size_t head_starts;
        size_t head_ends;
        int use_count;
        
        std::vector <o3cw::CDoc *> opened_docs;
    };
}

#endif	/* _CCLIENT_H */

