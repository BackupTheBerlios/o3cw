// 
// File:   csql.h
// Author: alex
//
// Created on 4 Май 2008 г., 23:55
//

#ifndef _CSQL_H
#define	_CSQL_H

#include <string>
#include <vector>

#include "cthreadsafeobject.h"

#define O3CW_SQL_NO_MORE_DATA 100

namespace o3cw
{
    class CSQL: public o3cw::CThreadSafeObject
    {
    public:
        CSQL();
        virtual ~CSQL();
        
        /* Connect to specified SQL server */
        virtual int Connect(std::string &host, std::string &db_name, std::string &user, std::string &password);
        
        /* Returns 0 if connection OK */
        virtual int Ping();
        
        /* Disconnect from SQL server */
        virtual int Disconnect();
        
        /* Perfrom SQL reqest given in request variable. Returns 0 on sucess */
        virtual int SQLRequest(std::string &request);
        virtual int SQLRequest(const char *request);
        virtual int SQLRequest(const char *request, size_t req_size);
        
        /* Fill up buff by next data set from previous SQL request (usually "select") */
        virtual int GetNextDataSet(std::vector<std::string> &buff);
        
        /* Finish request */
        virtual int FinishRequest();
        
        /* Thread initialize */
        virtual void ThreadStart();
        
        /* Thread DEinitialize */
        virtual void ThreadEnd();
        
        /* Global SQL library init function */
        static int Init();
        static int DeInit();
    protected:
        std::string m_host;
        std::string m_db_name;
        std::string m_user;
        std::string m_password;
        bool m_connected;
        
    };
}

#endif	/* _CSQL_H */

