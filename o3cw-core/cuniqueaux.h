// 
// File:   cuniqueaux.h
// Author: alex
//
// Created on 8 Апрель 2008 г., 16:15
//

#ifndef _CUNIQUEAUX_H
#define	_CUNIQUEAUX_H

#include <list>

#include "types.h"

namespace o3cw
{
    /*
     * This class keeps list of used IDs and some internal data
     * for CIdsObject class.
     *
     * NOTE:
     * If you want to create objects with unique IDs using CIdsObjet class,
     * they must pass the same CUniqueAux object to CIdsObject's construtor
     *
     */
    class CIdsObject;
    class CUniqueAux
    {
    public:
        CUniqueAux(){current_id=0;};
        ~CUniqueAux(){};
        friend class CIdsObject;
    private:
        o3cw::ids current_id;
        bonbon::CMutex id_lock;
        std::list<o3cw::ids *> id_list;
    };
}

#endif	/* _CUNIQUEAUX_H */

