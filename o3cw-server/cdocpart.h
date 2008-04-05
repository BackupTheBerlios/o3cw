// 
// File:   cdocpart.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 0:14
//

#ifndef _CDOCPART_H
#define	_CDOCPART_H

#include <string>
#include <vector>

#include "libbonbon.h"
#include "types.h"
#include "cdiff.h"
#include "csharedobject.h"

namespace o3cw
{
    class CClient;
    
    class CDocPart: public o3cw::CShareObject
    {
    public:
        CDocPart();
        ~CDocPart();

        //Full buff with doc_data content
        int GetPart(std::string &buff);
        
        //Add new diff, specified by buff
        o3cw::ids AddDiff(std::string &buff);
        
        //Accept specified diff by specified client
        int AcceptDiff(o3cw::CClient &client, o3cw::ids diff_id);
        
        //Commit diff means aplly diff - delete it from list and request full
        //part from diff creator
        int CommitDiff(o3cw::ids diff_id);
        
        //Cancel diff with id diff_id create by specified client.
        int RecallDiff(o3cw::CClient &client, o3cw::ids diff_id);
        
        //Returns parts (approximate?) size (in bytes). Used for lazy updates
        //(compare with sum of all diffs)
        size_t GetSize();
    private:
        //Example of an internal lock
        //Use this for data protection in multithread env
        bonbon::CMutex self_lock1;

        //Raw document data
        std::string part_data;
        
        //List of all diffs, acociated with this part
        std::vector<CDiff> diffs;
        
    };
}

#endif	/* _CDOCPART_H */

