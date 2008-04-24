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
    class CUniqueAux;
    
    class CDoc: public o3cw::CIdsObject
    {
    public:
        CDoc();
        ~CDoc();
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
        
	int Open(o3cw::CClient &client);
	
	int MultiCast(o3cw::CCommand &cmd);
	
        int OpenFile(const char *filename);
        
        int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out);
	
	int SetId(std::string &new_id);
    private:
        //Example of an internal lock
        //Use this for data protection in multithread env
        bonbon::CMutex self_lock1;
        
        //List of clients, connected to this document for broadcast
        std::vector<o3cw::CClient *> clients_connected;
        
        //List of documents parts
        std::vector<o3cw::CDocPart *> parts;
        
        //Keep parts ID values
        o3cw::CUniqueAux parts_unique_aux;
        
        //Keeps docs ID values
        static o3cw::CUniqueAux unique_data;
        
        /* REMOVE THIS */
        std::string content;
	
	std::string id;
        
    };
}

#endif	/* _CDOC_H */

