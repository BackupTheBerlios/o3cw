
#include <mysql/mysql_version.h>
#include <mysql/mysqld_error.h>

#include "cmysql.h"

o3cwapp::CMySQL::CMySQL(): o3cw::CSQL::CSQL()
{
    mysql_init(&m_connection);
    m_recving_data=false;
    m_quest_res=0;
    max_reconnect_attemps=5;
}

o3cwapp::CMySQL::~CMySQL()
{
    if (m_recving_data)
        FinishRequest();
    mysql_close(&m_connection);
}

int o3cwapp::CMySQL::Connect(std::string &host, std::string &db_name, std::string &user, std::string &password)
{
    o3cw::CSQL::Connect(host, db_name, user, password);
    MYSQL *tmp=mysql_real_connect(&m_connection, host.c_str(), user.c_str(), password.c_str(), db_name.c_str(), 0, 0, 0);
    if (tmp==0)
        return -1;
    return 0;
}

int o3cwapp::CMySQL::Ping()
{
    return 0;
}

int o3cwapp::CMySQL::Disconnect()
{
    mysql_close(&m_connection);
    return 0;
}

int o3cwapp::CMySQL::SQLRequest(const char *request)
{
    return SQLRequest(request, strlen(request));
}

int o3cwapp::CMySQL::SQLRequest(const char *request, size_t req_size)
{
    o3cw::CO3CWBase::GetMainConfig().GetValue(max_reconnect_attemps,"timeout","db");

    if (m_recving_data)
        FinishRequest();
    int sql_err=0;
    printf("MYSQL: [%s]\n", request);
    int err=mysql_real_query(&m_connection, request, req_size);
    while (err!=0)
    {
        sql_err=mysql_errno(&m_connection);
	printf("sql_err=%i\n", sql_err);

        /* Wrong MYSQL query. Shutdown. */
        if (ER_PARSE_ERROR==sql_err)
        {
	    printf("return 1");
            return -1;
        }
        else if (ER_BAD_FIELD_ERROR==sql_err)
        {
	    printf("return 2");
            return -2;
        }
        else if (ER_EMPTY_QUERY==sql_err)
        {
	    printf("return 3");
            return -3;
        }
        if (ER_DUP_ENTRY==sql_err)
        {
	    printf("return 4");
            return -4;
        }
        else if (ER_NO_SUCH_TABLE==sql_err)
        {
	    printf("return 5");
            return -5;
        }
        else
        {
                int restore_result=-1;
                int restore_count=1;
                while (restore_result!=0)
                {
                    /* Restore SQL  connection...*/
                    Connect(m_host, m_db_name, m_user, m_password);

                    if (restore_count<max_reconnect_attemps)
                            restore_count++;
                    else
                        return -6;

                    if (CR_SERVER_GONE_ERROR==sql_err || CR_SERVER_LOST==sql_err || CR_SERVER_HANDSHAKE_ERR==sql_err)
                            sleep(1);
                    else
                    {
                            /* Not CR_SERVER_GONE_ERROR, CR_SERVER_LOST, CR_SERVER_HANDSHAKE_ERR error, sleeping 1 sec */
                            sleep(1);
                    }
                }
                err=mysql_real_query(&m_connection, request, req_size);
                sql_err=mysql_errno(&m_connection);
            }
    }
    return 0;

}

int o3cwapp::CMySQL::SQLRequest(std::string &request)
{
    return SQLRequest(request.c_str(), request.length());
}

int o3cwapp::CMySQL::GetNextDataSet(std::vector<std::string> &buff)
{
    if (false==m_recving_data)
    {
        m_quest_res=mysql_store_result(&m_connection);
        if (m_quest_res!=0)
            m_recving_data=true;
        else
            return -1;
    }
    
    m_row=mysql_fetch_row(m_quest_res);
    unsigned long *lengths = mysql_fetch_lengths(m_quest_res);

    unsigned int num_fields=mysql_num_fields(m_quest_res);
    if (m_row!=0)
    {
        for (unsigned int i=0; i<num_fields; i++)
        //for (it=buff.begin(); it!=buff.end() && i<num_fields; it++)
        {
            if (buff.size()<(i+1))
                buff.push_back(std::string());
            
            if (m_row[i]!=0)
            {
                buff[i].assign(m_row[i], lengths[i]);
            }
            else
            {
                /* else WHAT? */
            }
        }
    }
    else
    {
        return O3CW_SQL_NO_MORE_DATA;
    }
    return 0;
}

int o3cwapp::CMySQL::FinishRequest()
{
    if (m_recving_data)
    {
        if (m_quest_res!=0)
            mysql_free_result(m_quest_res);
        m_recving_data=false;
    }
    return 0;
}

void o3cwapp::CMySQL::ThreadStart()
{
    mysql_thread_init();
    return;
}

void o3cwapp::CMySQL::ThreadEnd()
{
    mysql_thread_end();
    return;
}

int o3cwapp::CMySQL::Init()
{
    mysql_library_end();
    return 0;
}

int o3cwapp::CMySQL::DeInit()
{
    mysql_library_end();
    return 0;
}

std::string &o3cwapp::CMySQL::SQLSafeStr(std::string &str)
{
    int l=str.length()*2+1;
    if (l>1024)
    {
        char *buff=new char[l];
        unsigned long size=mysql_real_escape_string(&m_connection, buff, str.c_str(), str.length());
        str.assign(buff, size);
    }
    else
    {
        char buff[1024];
        unsigned long size=mysql_real_escape_string(&m_connection, buff, str.c_str(), str.length());
        str.assign(buff, size);
    }
    return str;
}
