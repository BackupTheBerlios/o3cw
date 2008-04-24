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
        CCommand(o3cw::CClient &cl, std::string *head, std::string *body);
        CCommand(o3cw::CClient &cl);
        ~CCommand();
	int Parse();
        int Compile(std::string &buff);
	void FreeCryptedData();
	std::string &Pop();
        int Push(std::string &data);
        int Push(const char *data);
        int Push(const char *data, size_t data_size);
        o3cw::CClient &GetClient();
	bool CmdAviable();
    private:
        std::string *body;
	std::string *head;
        o3cw::CClient *client;
	std::vector<std::string> cmds;
	std::vector<std::string>::iterator cur_val;
    };
}

#endif	/* _CCOMMAND_H */

