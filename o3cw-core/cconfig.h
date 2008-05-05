// 
// File:   cconfig.h
// Author: alex
//
// Created on 7 Апрель 2008 г., 18:30
//

#ifndef _CCONFIG_H
#define	_CCONFIG_H

#include <string>

#include "csharedobject.h"

namespace o3cw
{
    class CConfig: public o3cw::CSharedObject
    {
    public:
        CConfig();
        virtual ~CConfig();
        virtual int GetValue(std::string &buff, const char *param, const char *section) const;
        virtual int GetValue(long long &buff, const char *param, const char *section) const;
        virtual int GetValue(long &buff, const char *param, const char *section) const;
        virtual int GetValue(int &buff, const char *param, const char *section) const;
        virtual int GetValue(float &buff, const char *param, const char *section) const;
        
        template <class T>
        T &ReturnValue(T &buff, const char *param, const char *section) const
        {
            GetValue(buff, param, section);
            return buff;
        };
        
        virtual int Parse(const char *text);
        virtual int ParseFile(const char *filename);
        static int SimpleParse(std::string &text, std::string &tag_start, std::string &tag_end, std::string &value);
        static int SimpleParse(const char *text, const char *tag_start, const char *tag_end, std::string &value);
    private:
//        tinyxml::TiXmlDocument config;
        //TiXmlDocument config;
    };
}

#endif	/* _CCONFIG_H */

