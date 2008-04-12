#include "cconfig.h"

o3cw::CConfig::CConfig()
{
    
}

o3cw::CConfig::~CConfig()
{
    
}

int o3cw::CConfig::Parse(const char *text)
{
    if (text==NULL)
        return -1;
    
    config.Clear();
    config.Parse(text);
}

int o3cw::CConfig::GetValue(std::string &buff, const char *param, const char *section)
{
    std::string nodename;
    TiXmlNode *xml_node=config.FirstChildElement("config");
    if (xml_node==NULL)
        return -1;
    if (param==NULL || section==NULL)
        return -4;
    const char *p1=strstr(section, ":");
    if (p1==NULL)
    {
        
        nodename=section;
        xml_node=xml_node->FirstChildElement(section);
        if (xml_node==NULL)
            return -5;
    }
    else
    {
        //p1++;
        bool working=true;
        while (working)
        {
            nodename.assign(section, 0, p1-section);
            section=p1;
            xml_node=xml_node->FirstChildElement(nodename.c_str());
            if (xml_node==NULL)
                return -5;
            if (section[0]==0)
                working=false;
            section++;
            p1=strstr(section, ":");
            if (p1==NULL)
                p1=section+strlen(section);
            else
                p1++;
        }
    }
    TiXmlElement *xml_element=xml_node->FirstChildElement(param);
    if (xml_element!=NULL)
    {
        if (xml_element->GetText()!=NULL)
        {
            buff.assign(xml_element->GetText());
            return 0;
        }
        return -2;
    }
    return -3;
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
