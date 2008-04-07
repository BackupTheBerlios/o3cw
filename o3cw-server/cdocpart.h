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
    class CStorage;
    
    class CDocPart: public o3cw::CSharedObject
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
        
        //Cancel diff with id diff_id create by specified client
        int RecallDiff(o3cw::CClient &client, o3cw::ids diff_id);
        
        //Returns parts (approximate?) size (in bytes). Used for lazy updates
        //(compare with sum of all diffs)
        size_t GetSize();
        
        //Copy part content to cache (e.x., hard drive)
        //and cleanup content (part_data)
        int MoveToCahe(o3cw::CStorage &cache);
        
        //Copy last_activity_time into buff
        void GetLastActivityTime(long long &buff);
    private:
        //Example of an internal lock
        //Use this for data protection in multithread env
        bonbon::CMutex self_lock1;

        //Raw document data
        std::string part_data;
        
        //List of all diffs, acociated with this part
        std::vector<CDiff> diffs;
        
        //Indicates last time of *Part and *Diff functions
        long long last_activity_time;
        
        //Handle storage where part was cached last time; null if part is loaded
        o3cw::CStorage *cached_in;
        
        //Keep full parts adress in cache
        std::string name_in_cache;
    };
}

#endif	/* _CDOCPART_H */

