// 
// File:   cdifferenced.h
// Author: alex
//
// Created on 12 Май 2008 г., 22:06
//

#ifndef _CDIFFERENCED_H
#define	_CDIFFERENCED_H

//#include <vector>

#include "cidsobject.h"
#include "cdoc.h"

namespace o3cw
{
    class CUser;
    class CDiff;
    class CClient;
    class CDifferenced: public o3cw::CIdsObject
    {
    public:
        CDifferenced(o3cw::CDifferenced &prnt, o3cw::CUniqueAux &daux);
        virtual ~CDifferenced();
        int AddDiff(const std::string &diff_content, const o3cw::CHash &diff_hash, o3cw::CUser &user);
        int ConfirmDiff(o3cw::CHash &diff_hash, o3cw::CUser &user);
        int RejectDiff(o3cw::CHash &diff_hash, o3cw::CUser &user);
        int RecallDiff(o3cw::CHash &diff_hash, o3cw::CUser &user);
        int AcceptDiff(o3cw::CHash &diff_hash, o3cw::CUser &user);
    protected:
        virtual std::vector<o3cw::CClient *> &GetClientsConnected(){return m_parent.GetClientsConnected();}
        virtual o3cw::CDoc &GetParentDoc(){return m_parent.GetParentDoc();}
    private:
        o3cw::CDifferenced &m_parent;
        std::vector<o3cw::CDiff *> m_diffs;
        o3cw::CDiff *FindDiff(const o3cw::CHash &diff_hash);
    };
}

#endif	/* _CDIFFERENCED_H */

