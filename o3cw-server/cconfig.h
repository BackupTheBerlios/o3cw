// 
// File:   cconfig.h
// Author: alex
//
// Created on 7 Апрель 2008 г., 18:30
//

#ifndef _CCONFIG_H
#define	_CCONFIG_H

#include <string>

#include "tinyxml.h"

namespace o3cw
{
    class CConfig
    {
    public:
        CConfig();
        ~CConfig();
        int GetValue(std::string &buff, const char *param, const char *section);
        int SetValue(const char *value, const char *param, const char *section);
        int Parse(const char *text);
        int ParseFile(const char *filename);
        static int SimpleParse(std::string &text, std::string &tag_start, std::string &tag_end, std::string &value);
        static int SimpleParse(const char *text, const char *tag_start, const char *tag_end, std::string &value);
    private:
        //tinyxml::TiXmlDocument config;
        TiXmlDocument config;
    };
}

#endif	/* _CCONFIG_H */

