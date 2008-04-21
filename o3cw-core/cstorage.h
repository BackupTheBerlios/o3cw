// 
// File:   cstorage.h
// Author: alex
//
// Created on 7 Апрель 2008 г., 15:21
//

#ifndef _CSTORAGE_H
#define	_CSTORAGE_H

#include <string>

#include "csharedobject.h"

namespace o3cw
{    
    class CPart;
    class CStorage: public o3cw::CSharedObject
    {
    public:
        CStorage();
        ~CStorage();
        
        //Load raw doc data, located at adress to buff
        virtual int LoadDoc(const char *adress, std::string &buff);
        
        //Write raw doc data from buff to adress
        virtual int WriteDoc(const char *adress, std::string &buff);
        
        //Delete doc located at adress
        virtual int DeleteDoc(const char *adress);
        
        //Copy doc from src_adress to dest_adress
        virtual int CopyDoc(const char *src_adress, const char *dest_adress);
        
    protected:
        friend class o3cw::CPart;
        //Load raw part data, located at adress to buff
        virtual int LoadPart(const char *adress, std::string &buff);
        
        //Write raw part data from buff to adress
        virtual int WritePart(std::string &adress, std::string &buff);
        
        //Delete part located at adress
        virtual int DeletePart(const char *adress);
    };
}
#endif	/* _CSTORAGE_H */
