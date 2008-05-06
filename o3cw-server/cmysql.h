// 
// File:   cmysql.h
// Author: alex
//
// Created on 5 Май 2008 г., 0:36
//

#ifndef _CMYSQL_H
#define	_CMYSQL_H

#include <mysql/mysql.h>
#include <mysql/mysql_com.h>
#include <mysql/errmsg.h>

#include "../o3cw-core/o3cw.h"

namespace o3cwapp
{
    class CMySQL: public o3cw::CSQL
    {
    public:
        CMySQL();
        virtual ~CMySQL();
        
        /* Connect to specified SQL server */
        int Connect(std::string &host, std::string &db_name, std::string &user, std::string &password);
        
        /* Returns 0 if connection OK */
        int Ping();
        
        /* Disconnect from SQL server */
        int Disconnect();
        
        /* Perfrom SQL reqest given in request variable. Returns 0 on sucess */
        int SQLRequest(std::string &request);
        int SQLRequest(const char *request);
        int SQLRequest(const char *request, size_t req_size);
        
        /* Fill up buff by next data set from previous SQL request (usually "select") */
        int GetNextDataSet(std::vector<std::string> &buff);
        
        /* Finish request */
        int FinishRequest();
        
        /* Thread initialize */
        void ThreadStart();
        
        /* Thread DEinitialize */
        void ThreadEnd();
        
        /* Global SQL library init function */
        static int Init();
        static int DeInit();
        
        std::string &SQLSafeStr(std::string &str);
    private:
        MYSQL m_connection;
        bool m_recving_data;
        MYSQL_RES *m_quest_res;
	MYSQL_ROW m_row;
    };
}

#endif	/* _CMYSQL_H */

