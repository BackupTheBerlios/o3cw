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

#include "libbonbon.h"
#include "types.h"
#include "cdocpart.h"
#include "csharedobject.h"

namespace o3cw
{
    class CDiff;
    class CClient;
    class CPermission;
    
    class CDoc: public o3cw::CShareObject
    {
    public:
        CDoc();
        ~CDoc();
        int Open(o3cw::CClient &client);
        int Close(o3cw::CClient &client);
        
        //Write document header into buff
        int GetHeader(std::string &buff);
        
        //Write all parts and diffs in buff
        int GetData(CClient &client, std::string &buff);
        
        //Add new diff to specified part by specified client
        int AddDiff(CClient &client, o3cw::ids part, std::string &diff_data);
        
        //Accept one specified diff by one specified user
        int AcceptDiff(CClient &client, o3cw::ids part, o3cw::ids diff);
        
        //Reject one specified diff by one specified client (conflict)
        int RejectDiff(CClient &client, o3cw::ids part, o3cw::ids diff);
        
        //Cancel one specified diff by one user
        int CancelDiff(CClient &client, o3cw::ids part, o3cw::ids diff);
        
        //Commit full part. All diff for this part will be deleted (?)
        int CommitPart(CClient &client, o3cw::ids part, std::string &part);
        
        //Divide part part_id by 2 parts, with part data in part1 and part2
        int DividePart(o3cw::CClient &client, o3cw::ids part, std::string &part1, std::string &part2);
        
        //Delete part with specified id
        int DeletePart(o3cw::CClient &client, o3cw::ids part_id);
        
        //Change part part_id permission to specified
        int PartChangePermissions(o3cw::CClient &client, o3cw::ids part, o3cw::CPermission &new_perm);

    private:
        //Example of an internal lock
        //Use this for data protection in multithread env
        bonbon::CMutex self_lock1;
        
        //List of clients, connected to this document for broadcast
        std::vector<o3cw::CClient *> clients_connected;
        
        //List of documents parts
        std::vector<o3cw::CDocPart> parts;
    };
}

#endif	/* _CDOC_H */

