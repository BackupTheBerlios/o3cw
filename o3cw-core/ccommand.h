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
        CCommand();
        ~CCommand();
	int Parse();
        o3cw::CClient *client;
        std::string crypted_cmd;
        std::queue<std::string *> cmds;
    };
}

#endif	/* _CCOMMAND_H */

