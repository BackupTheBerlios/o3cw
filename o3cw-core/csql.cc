#include "csql.h"

o3cw::CSQL::CSQL(): o3cw::CThreadSafeObject::CThreadSafeObject()
{
    m_connected=false;
}

o3cw::CSQL::~CSQL()
{
    
}

int o3cw::CSQL::Connect(std::string &host, std::string &db_name, std::string &user, std::string &password)
{
    if (m_connected)
        Disconnect();
    m_host=host;
    m_db_name=db_name;
    m_user=user;
    m_password=password;
    return 0;
}

int o3cw::CSQL::Ping()
{
    return 0;
}

int o3cw::CSQL::Disconnect()
{
    m_connected=false;
    return 0;
}

int o3cw::CSQL::SQLRequest(const char *request)
{
    return 0;
}

int o3cw::CSQL::SQLRequest(const char *request, size_t req_size)
{
    return 0;
}

int o3cw::CSQL::SQLRequest(std::string &request)
{
    return 0;
}

int o3cw::CSQL::GetNextDataSet(std::vector<std::string> &buff)
{
    return 0;
}

int o3cw::CSQL::FinishRequest()
{
    return 0;
}

void o3cw::CSQL::ThreadStart()
{
    return;
}

void o3cw::CSQL::ThreadEnd()
{
    return;
}

int o3cw::CSQL::Init()
{
    return 0;
}

int o3cw::CSQL::DeInit()
{
    return 0;
}

std::string &o3cw::CSQL::SQLSafeStr(std::string &str)
{
    return str;
}

void o3cw::CSQL::NumToStr(char *buff, size_t buff_size, int v)
{
    snprintf(buff, buff_size, "%i", v);
}
void o3cw::CSQL::NumToStr(char *buff, size_t buff_size, long v)
{
    snprintf(buff, buff_size, "%li", v);
}
void o3cw::CSQL::NumToStr(char *buff, size_t buff_size, long long v)
{
    snprintf(buff, buff_size, "%lli", v);
}
void o3cw::CSQL::NumToStr(char *buff, size_t buff_size, float v)
{
    snprintf(buff, buff_size, "%f", v);
}
