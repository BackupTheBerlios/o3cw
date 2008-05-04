// 
// File:   cstorage.h
// Author: alex
//
// Created on 7 Апрель 2008 г., 15:21
//

#ifndef _CSTORAGE_H
#define	_CSTORAGE_H

#include <string>
#include <map>

#include "csharedobject.h"
#include "chashkey.h"

namespace o3cw
{ 
    class CDoc;
    class CPart;
    class CStorage: public o3cw::CSharedObject
    {
    public:
        CStorage();
        virtual ~CStorage();
        
        //Load raw doc data, located at adress to buff
        int LoadDoc(const char *adress, std::string &buff);
        
        //Write raw doc data from buff to adress
        int WriteDoc(const char *adress, std::string &buff);
        
        //Delete doc located at adress
        int DeleteDoc(const char *adress);
        
        //Copy doc from src_adress to dest_adress
        int CopyDoc(const char *src_adress, const char *dest_adress);
	
	int ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out);
        
    protected:
        friend class o3cw::CPart;
        //Load raw part data, located at adress to buff
        int LoadPart(const char *adress, std::string &buff);
        
        //Write raw part data from buff to adress
        int WritePart(std::string &adress, std::string &buff);
        
        //Delete part located at adress
        int DeletePart(const char *adress);
        
    private:
        //o3cw::CHexTree<o3cw::CDoc> docs;
        std::map<o3cw::CHashKey, o3cw::CDoc *> docs;
	

    };
}
#endif	/* _CSTORAGE_H */
