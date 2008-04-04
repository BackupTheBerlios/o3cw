// 
// File:   cdoc.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 0:04
//

#ifndef _CDOC_H
#define	_CDOC_H

#include <string>
#include <vector>

#include "cclient.h"
#include "cdiff.h"

namespace o3cw
{
    class CDiff;
    class CClient;
    
    class CDoc
    {
    public:
        CDoc();
        ~CDoc();
        int Open(o3cw::CClient &user);
        int Close(o3cw::CClient &user);
        virtual int GetDiff(o3cw::CDiff &diff);
        virtual int CommitDiff(o3cw::CDiff &diff);
        virtual int GetXMLData(std::string &buff);
        virtual int CommitXMLData(std::string &buff);
    private:
        std::vector<o3cw::CClient *> users_connected;
    };
}

#endif	/* _CDOC_H */

