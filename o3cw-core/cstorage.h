// 
// File:   cstorage.h
// Author: alex
//
// Created on 7 Апрель 2008 г., 15:21
//

#ifndef _CSTORAGE_H
#define	_CSTORAGE_H

#include <string>
#include <map>

#include "csharedobject.h"
#include "chashkey.h"

#include "ccrypto.h"
#include "cstoreobjwrapper.h"

namespace o3cw
{ 
    class CStorage: public o3cw::CSharedObject
    {
    public:
        CStorage(const char *type);
        virtual ~CStorage();
        
	int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out);
        
        virtual void DeleteUnusedElements();
    private:
        std::map<o3cw::CHashKey, o3cw::CIdsObject *> store;
	o3cw::CStoreObjWrapper objwrapp;

    };
}

#endif	/* _CSTORAGE_H */
