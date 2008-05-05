// 
// File:   cxmlconfig.h
// Author: alex
//
// Created on 5 Май 2008 г., 16:03
//

#ifndef _CXMLCONFIG_H
#define	_CXMLCONFIG_H

#include "../o3cw-core/o3cw.h"
#include "tinyxml.h"

namespace o3cwapp
{
    class CXMLConfig: public o3cw::CConfig
    {
    public:
        CXMLConfig();
        ~CXMLConfig();
        int GetValue(std::string &buff, const char *param, const char *section) const;
        int GetValue(long long &buff, const char *param, const char *section) const;
        int GetValue(long &buff, const char *param, const char *section) const;
        int GetValue(int &buff, const char *param, const char *section) const;
        int GetValue(float &buff, const char *param, const char *section) const;
        
        int Parse(const char *text);
        int ParseFile(const char *filename);
    private:
        tinyxml::TiXmlDocument config;
    };
}

#endif	/* _CXMLCONFIG_H */

