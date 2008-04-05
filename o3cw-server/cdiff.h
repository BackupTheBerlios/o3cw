// 
// File:   cdiff.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 0:04
//

#ifndef _CDIFF_H
#define	_CDIFF_H

#include <string>

#include "libbonbon.h"
#include "types.h"
#include "csharedobject.h"

namespace o3cw
{
    class CClient;
    class CDiff: public o3cw::CShareObject
    {
    public:
        CDiff(o3cw::ids client_id, o3cw::ids part_id, o3cw::ids diff_id);
        ~CDiff();
        o3cw::CDiff &operator=(const o3cw::CDiff &d);
        bool operator==(const o3cw::CDiff &d);

        //Accept diff by specified client (add to accepted_by)
        int Accept(o3cw::CClient &client);
        
        //Copy diff data to buff
        int GetDiff(std::string &buff);
        
        //Returns diffs (approximate?) size (in bytes). Used for lazy updates
        //(compare with master-part size);
        unsigned int GetSize();
    private:
        //Example of an internal lock
        //Use this for data protection in multithread env
        bonbon::CMutex self_lock1;
    protected:
        //Creator id
        o3cw::ids client_id;
        
        //Master-part id
        o3cw::ids part_id;
        
        //List of clients, accepted this diff.
        std::vector<o3cw::CClient *> accepted_by;
        
        //If true, diff acepted by everyone already ("confirmed")
        bool confirmed;
        
        std::string diff_data;
    };
}


#endif	/* _CDIFF_H */

