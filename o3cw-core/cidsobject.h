// 
// File:   cidsobject.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 12:13
//

#ifndef _CIDSOBJECT_H
#define	_CIDSOBJECT_H

#include <list>
#include <string>

#include "types.h"
#include "csharedobject.h"
#include "libbonbon.h"
#include "cuniqueaux.h"
#include "chash.h"

namespace o3cw
{
    /*
     * Class CIdsOject provides a fast way to build objects with
     * unique numerical IDs. You must pass as parameters
     * CMutex lock, current_id initialized as 0 and list of used IDs.
     * They all must be static members of your child class, and you
     * should *never* change them manually. 
     */
    class CUniqueAux;
    class CIdsObject: public o3cw::CSharedObject
    {
    public:
        /*
         * id_lock, current_id and id_list must be static child class variables.
         * current_id must be a initialized by 0, and id_list must be empty.
         */
        CIdsObject(o3cw::CUniqueAux &aux);
        
        /* Destructor will cleanup list of used IDs automaticly! */
        virtual ~CIdsObject();
        
        /* Returns unique object id */
        o3cw::ids GetId() const;
        
        bool operator <(const CIdsObject &comp);
        
        int SetKey(o3cw::CHash &new_key);
        const o3cw::CHash &GetKey() const;
        
	std::vector<o3cw::CIdsObject *> &GetDeleteList(){return delete_list;}
	
        int Use();
        int UnUse();
        int GetUseCount();
	
	/* Execute "open" command. If *element is 0, that means that requested element does not
         * exists in store.
         * Open() can create new element (using "new" operator), initialize it
         * set *element pointer to created element and return 0,
         * OR
         * return non-zero error code and keep *element as 0.
         * If *element is not 0, that means that that requested element exists in store already,
         * and Open() needs just to return zero if client can open it or error code otherwise.
         */
        virtual int Open(o3cw::CCommand &cmd, o3cw::CCommand &out, o3cw::CIdsObject **element);

    private:
	static std::vector<o3cw::CIdsObject *> delete_list;
        /* Keeps unique object id */
        o3cw::ids obj_id;
        
        /*
         * Generates new ID, using id_lock for thread-safety, current_id as base,
         * and id_list as list of used ID's
         */
        void GenerateNewId(bonbon::CMutex &id_lock, o3cw::ids &current_id, std::list<o3cw::ids *> &id_list);
        
        /* Remove obj_id from id_list, using id_lock for thread-safety */
        void FreeMyId(bonbon::CMutex &id_lock, std::list<o3cw::ids *> &id_list);
        
        /* Used to store parametres passed to constructor */
        std::list<o3cw::ids *> *idlist;
        bonbon::CMutex *idlock;
        
        o3cw::CHash m_key;
        int m_use_count;
    };
}


#endif	/* _CIDSOBJECT_H */

