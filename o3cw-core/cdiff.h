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
#include "cidsobject.h"

namespace o3cw
{
    class CUser;
    class CClient;
    class CDocPart;
    class CDiff: public o3cw::CIdsObject
    {
    public:
        CDiff(std::string &data, std::string &data_hash, o3cw::CDocPart &docpart);
        virtual ~CDiff();
        o3cw::CDiff &operator=(const o3cw::CDiff &d);
        bool operator==(const o3cw::CDiff &d);

        //Accept diff by specified client (add to accepted_by)
        int Accept(o3cw::CClient &client);
        
        //Copy diff data to buff
        int GetDiff(std::string &buff);
        
        //Returns diffs (approximate?) size (in bytes). Used for lazy updates
        //(compare with master-part size);
        unsigned int GetSize();
        
        int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out);
    private:
        //List of clients, accepted this diff.
        std::vector<o3cw::CUser *> m_confirmed_by;
        
        //If true, diff confirmed by everyone already ("accepted")
        bool m_accepted;
        
        /* Diff data */
        std::string m_diff_data;
        
        /* Diff data hash */
        std::string m_diff_data_hash;
        
        /* Parent doc part */
        o3cw::CDocPart &m_parent_docpart;
        static o3cw::CUniqueAux diff_uaux;
        
    };
}


#endif	/* _CDIFF_H */

