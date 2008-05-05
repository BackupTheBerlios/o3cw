// 
// File:   cuser.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 9:15
//

#ifndef _CUSER_H
#define	_CUSER_H

#include <map>

#include "types.h"
#include "cidsobject.h"

namespace o3cw
{
    class CClient;
    class CUser: public o3cw::CIdsObject
    {
    public:
        CUser();
        virtual ~CUser();
        o3cw::ids GetUserId();
        static int StaticExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out);
        int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out);
        void GetName(std::string &buff);
    private:
        o3cw::ids user_id;
        static std::map<std::string, o3cw::CUser *> users;
        static o3cw::CUniqueAux unique_data;
        std::string name;
    };
}


#endif	/* _CUSER_H */

