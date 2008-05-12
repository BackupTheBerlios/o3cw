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
#include "cdifferenced.h"

namespace o3cw
{
    class CUser;
    class CClient;
    class CDocPart;
    class CHash;
    class CDiff: public o3cw::CDifferenced
    {
    public:
        CDiff(const std::string &data, const o3cw::CHash &key, o3cw::CDifferenced &prnt);
        virtual ~CDiff();
        o3cw::CDiff &operator=(const o3cw::CDiff &d);
        bool operator==(const o3cw::CDiff &d);

        /* Confirm diff by specified user */
        int ConfirmBy(o3cw::CUser &user);
        
        int RejectBy(o3cw::CUser &user);
        int RecallBy(o3cw::CUser &user);
        int AcceptBy(o3cw::CUser &user);
        
        //Copy diff data to buff
        int GetDiff(std::string &buff);
        
        //Returns diffs (approximate?) size (in bytes). Used for lazy updates
        //(compare with master-part size);
        unsigned int GetSize();
        
        int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out);
	
	int RemoveClientFromMulticast(const o3cw::CClient &client);
	
    private:

        /* List of clients, accepted this diff */
        std::vector<o3cw::CUser *> m_confirmed_by;
        
        //If true, diff confirmed by everyone already ("accepted")
        bool m_accepted;
        
        /* Diff data */
        std::string m_diff_data;
        
        /* Diff data hash */
        o3cw::CHash m_diff_data_hash;
        
        /* Parent doc part */
        o3cw::CDifferenced &m_parent;
        static o3cw::CUniqueAux diff_uaux;

	/* Check if diff accepted and multicast message about it.
	 * Returns true if multicast done.
	 * if ne�essary.
	 * Changes m_accepted value, not tread-safe. (mlock.Lock() first!)
	 */
	bool RefreshAccept();
	
	/* Returns true if diff accepted.
	 * Doesn't change m_accepted.
	 * Not tread-safe. (mlock.Lock() first!)
	 */
	bool CheckAccepted();

	
	
        
    };
}


#endif	/* _CDIFF_H */

