// 
// File:   ccommand.h
// Author: alex
//
// Created on 20 Апрель 2008 г., 10:45
//

#ifndef _CCOMMAND_H
#define	_CCOMMAND_H

#include <string>
#include <queue>

namespace o3cw
{
    class CClient;
    class CCommand
    {
    public:
        CCommand(o3cw::CClient &cl, std::string &data);
        CCommand(o3cw::CClient &cl);
        ~CCommand();
	int Parse();
        int Compile(std::queue<std::string *> &cmds, std::string &buff);
        int Compile(std::string &buff);
	int Get(std::string &buff);
	int Pop(std::string &buff);
	int Pop();
        int Push(std::string &data);
        int Push(const char *data);
        int Push(const char*data, size_t data_size);
        o3cw::CClient &GetClient();
    private:
        std::string crypted_data;
        o3cw::CClient *client;
        std::queue<std::string *> cmds;
    };
}

#endif	/* _CCOMMAND_H */

