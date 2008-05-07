#include <fstream>

#include "cxmlconfig.h"

o3cwapp::CXMLConfig::CXMLConfig(): o3cw::CConfig::CConfig()
{
    
}

o3cwapp::CXMLConfig::~CXMLConfig()
{
    
}

int o3cwapp::CXMLConfig::Parse(const char *text)
{
    if (text==NULL)
        return -1;
    
    config.Clear();
    config.Parse(text);
    return 0;
}

int o3cwapp::CXMLConfig::ParseFile(const char *filename)
{
    int result=0;
    if (filename==NULL)
	result=-1;
    else
    {
        std::fstream file;
	file.open(filename, std::fstream::in);
        if (file.good())
	{
	    file.seekg (0, std::ios::end);
	    int l = file.tellg();
	    file.seekg (0, std::ios::beg);
	    char *buff=new char [l+1];
	    if (buff!=NULL)
	    {
		memset(buff, 0, l+1);
		file.read(buff,l);
		result=Parse(buff);
		delete [] buff;
	    }
	    else
		result=O3CW_ERR_OUT_OF_MEM;
        }
	file.close();
    }
    return result;
}

int o3cwapp::CXMLConfig::GetValue(std::string &buff, const char *param, const char *section) const
{
    std::string nodename;
    const tinyxml::TiXmlNode *xml_node=config.FirstChildElement("config");
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
    const tinyxml::TiXmlElement *xml_element=xml_node->FirstChildElement(param);
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

int o3cwapp::CXMLConfig::GetValue(long long &buff, const char *param, const char *section) const
{
    int result=0;
    std::string s;
    if (GetValue(s, param, section)==0)
	buff=atoll(s.c_str());
    return result;
}
int o3cwapp::CXMLConfig::GetValue(long &buff, const char *param, const char *section) const
{
    int result=0;
    std::string s;
    if (GetValue(s, param, section)==0)
	buff=atol(s.c_str());
    return result;
}

int o3cwapp::CXMLConfig::GetValue(int &buff, const char *param, const char *section) const
{
    int result=0;
    std::string s;
    if (GetValue(s, param, section)==0)
	buff=atoi(s.c_str());
    return result;
}

int o3cwapp::CXMLConfig::GetValue(float &buff, const char *param, const char *section) const
{
    int result=0;
    std::string s;
    GetValue(s, param, section);
    buff=atof(s.c_str());
    return result;
}
