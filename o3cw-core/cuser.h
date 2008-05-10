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
        CUser(long user_id);
        virtual ~CUser();
        int Open(o3cw::CCommand &cmd, o3cw::CCommand &out, o3cw::CIdsObject **e);
        int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &out);
        void GetName(std::string &buff);
        long GetUserId() const;
        int ClientRegister(o3cw::CClient &client);
        int ClientUnRegister(o3cw::CClient &client);
    private:
        long m_user_id;
        //static std::map<std::string, o3cw::CUser *> m_users;
        static o3cw::CUniqueAux unique_data;
        std::string m_name;
        std::vector<o3cw::CClient *> m_clients;
    };
}


#endif	/* _CUSER_H */

