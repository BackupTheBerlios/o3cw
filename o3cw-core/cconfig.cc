#include <fstream>

#include "cconfig.h"
#include "csharedobject.h"
#include "error.h"

o3cw::CConfig::CConfig(): o3cw::CSharedObject::CSharedObject()
{
    
}

o3cw::CConfig::~CConfig()
{
    
}

int o3cw::CConfig::Parse(const char *text)
{
    return 0;
}

int o3cw::CConfig::ParseFile(const char *filename)
{
    return 0;
}

int o3cw::CConfig::GetValue(std::string &buff, const char *param, const char *section) const
{
    return 0;
}

int o3cw::CConfig::GetValue(long long &buff, const char *param, const char *section) const
{
    return 0;
}
int o3cw::CConfig::GetValue(long &buff, const char *param, const char *section) const
{
    return 0;
}

int o3cw::CConfig::GetValue(int &buff, const char *param, const char *section) const
{
    return 0;
}

int o3cw::CConfig::GetValue(float &buff, const char *param, const char *section) const
{
    return 0;
}
        

int o3cw::CConfig::SimpleParse(const char *text, const char *tag_start, const char *tag_end, std::string &value)
{
    if (text==NULL || tag_start==NULL || tag_end==NULL)
        return -1;
    const char *ptr1=strstr(text, tag_start);
    if (ptr1!=NULL)
    {
        ptr1+=strlen(tag_start);
        const char *ptr2=strstr(ptr1, tag_end);
        if (ptr2!=NULL)
        {
            value.assign(ptr1, ptr2-ptr1);
        }
        else
            return 2;
    }
    else
        return 1;
    return 0;
}

int o3cw::CConfig::SimpleParse(std::string &text, std::string &tag_start, std::string &tag_end, std::string &value)
{
    return o3cw::CConfig::SimpleParse(text.c_str(), tag_start.c_str(), tag_end.c_str(), value);
}
