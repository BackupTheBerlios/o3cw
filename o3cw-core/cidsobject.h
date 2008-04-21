// 
// File:   cidsobject.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 12:13
//

#ifndef _CIDSOBJECT_H
#define	_CIDSOBJECT_H

#include <list>

#include "types.h"
#include "csharedobject.h"
#include "libbonbon.h"
#include "cuniqueaux.h"

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
        ~CIdsObject();
        
        /* Returns unique object id */
        o3cw::ids GetId();
        
    private:
        
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
    };
}


#endif	/* _CIDSOBJECT_H */

