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
    class CUniqueAux;
    class CDoc;
    
    class CDocPart: public o3cw::CDifferenced
    {
    public:
        CDocPart(o3cw::CDoc &parentdoc);
        virtual ~CDocPart();

        //Full buff with doc_data content
        int GetPart(std::string &buff);
        
        //Returns parts (approximate?) size (in bytes). Used for lazy updates
        //(compare with sum of all diffs)
        size_t GetSize();
        
        //Copy part content to cache (e.x., hard drive)
        //and cleanup content (part_data)
        int MoveToCahe(o3cw::CStorage &cache);
        
        //Copy last_activity_time into buff
        void GetLastActivityTime(long long &buff);
        
        int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out);
        
	o3cw::CDoc &m_parent_doc;
	int RemoveClientFromMulticast(const o3cw::CClient &client);
        std::vector<o3cw::CClient *> &GetClientsConnected(){return m_parent_doc.clients_connected;}
        o3cw::CDoc &GetParentDoc(){return m_parent_doc;}
    private:
        //Example of an internal lock
        //Use this for data protection in multithread env
        bonbon::CMutex self_lock1;

        //Raw document data
        std::string part_data;
        
        //List of all diffs, acociated with this part
        std::vector<o3cw::CDiff *> diffs;
        
        //Indicates last time of *Part and *Diff functions
        long long last_activity_time;
        
        //Handle storage where part was cached last time; null if part is loaded
        o3cw::CStorage *cached_in;
        
        //Keep full parts adress in cache
        std::string name_in_cache;
        
        static o3cw::CUniqueAux diffs_unique_aux;

    };
}

#endif	/* _CDOCPART_H */

