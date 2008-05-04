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
