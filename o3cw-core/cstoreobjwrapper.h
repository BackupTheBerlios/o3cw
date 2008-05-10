// 
// File:   cstoreobjwrapper.h
// Author: alex
//
// Created on 9 Май 2008 г., 23:02
//

#ifndef _CSTOREOBJWRAPPER_H
#define	_CSTOREOBJWRAPPER_H

#include "cidsobject.h"

namespace o3cw
{
    class CStoreObjWrapper
    {
    public:
        CStoreObjWrapper(const char *type);
        virtual ~CStoreObjWrapper();
        int Open(o3cw::CCommand &cmd, o3cw::CCommand &out, o3cw::CIdsObject **element);
        void ElementsLock(){pattern->GetClassMLock().Lock();}
        void ElementsUnLock(){pattern->GetClassMLock().UnLock();}
        std::vector<o3cw::CIdsObject *> &GetDeleteList(){return pattern->GetDeleteList();}
    private:
        o3cw::CIdsObject *pattern;
    };
}


#endif	/* _CSTOREOBJWRAPPER_H */

