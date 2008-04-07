// 
// File:   cconfig.h
// Author: alex
//
// Created on 7 Апрель 2008 г., 18:30
//

#ifndef _CCONFIG_H
#define	_CCONFIG_H

#include <string>

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
        void Clean();
    };
}

#endif	/* _CCONFIG_H */

