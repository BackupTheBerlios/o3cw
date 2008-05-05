// 
// File:   ccmdexec.h
// Author: alex
//
// Created on 20 Апрель 2008 г., 10:39
//

#ifndef _CCMDEXEC_H
#define	_CCMDEXEC_H

#include "cnetwork.h"

namespace o3cw
{
    class CSQL;
    class CCmdExec: public o3cw::CNetwork
    {
    public:
        CCmdExec();
        virtual ~CCmdExec();
        int ThreadExecute();
        o3cw::CSQL &SQL();
        int Run(o3cw::CSQL &sql_connection);
    private:
        void CleanUp();
        o3cw::CSQL *m_sql_connection;
    };
}

#endif	/* _CCMDEXEC_H */

