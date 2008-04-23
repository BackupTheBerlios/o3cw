// 
// File:   ccrypto.h
// Author: alex
//
// Created on 23 Апрель 2008 г., 7:44
//

#ifndef _CCRYPTO_H
#define	_CCRYPTO_H

#include <string>

namespace o3cw
{
    class CCrypto
    {
    public:
        CCrypto();
        ~CCrypto();
        static int MD5HashHex(std::string &data, std::string &buff);
        static int MD5HashBin(std::string &data, std::string &buff);
        static void Base64Encode(const unsigned char* input,size_t l,std::string& output);
        static int Base64Decode(const char *input, std::string &out);
    };
}

#endif	/* _CCRYPTO_H */

