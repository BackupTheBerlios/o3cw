// 
// File:   chash.h
// Author: alex
//
// Created on 13 Май 2008 г., 0:40
//

#ifndef _CHASH_H
#define	_CHASH_H

#include "ccrypto.h"

namespace o3cw
{
    class CHash: public o3cw::CThreadSafeObject
    {
    public:
        CHash(){};
        CHash(const std::string &md5data)
        {
            memset(p, 0, sizeof(p));
            const char *ptr=md5data.c_str();
            size_t s=md5data.length();
            int i=0;
            while (s>0 && i<3)
            {
                if (s>sizeof(p[i]))
                {
                    memcpy(&p[i], ptr, sizeof(p[i]));
                    ptr+=sizeof(p[i]);
                    s-=sizeof(p[i]);
                }
                else
                {
                    memcpy(&p[i], ptr, s);
                    s=0;
                }
                i++;
            }
            o3cw::CCrypto::Base64Encode((const unsigned char*)p, sizeof(p),base64_value);
        }
        virtual ~CHash(){};
        bool operator<(const CHash& cmp) const
        {
            class_mlock.Lock();
            int i=0;
            while (i<3)
            {
                if (cmp.p[i]>p[i])
                {
                    class_mlock.UnLock();
                    return true;
                }
                else if(cmp.p[i]<p[i])
                {
                    class_mlock.UnLock();
                    return false;
                }
                i++;
            }
            class_mlock.UnLock();
            return false;
        }
        CHash &operator=(const CHash& v)
        {
            class_mlock.UnLock();
            memcpy(p, v.p, sizeof(p));
            mlock.Lock();
            o3cw::CCrypto::Base64Encode((const unsigned char*)p, sizeof(p),base64_value);
            mlock.UnLock();
            class_mlock.UnLock();
            return *this;
        }
        std::string &GetBase64Value(std::string &buff) const
        {
            mlock.Lock();
            buff=base64_value;
            mlock.UnLock();
            return buff;
        }
        bool operator==(const CHash& v) const
        {
            bool result=false;
            class_mlock.Lock();
            if (p[0]==v.p[0] && p[1]==v.p[1] && p[2]==v.p[2])
                result=true;
            class_mlock.UnLock();
            return result;
        }
    private:
        std::string base64_value;
        long long p[3];
    };
}


#endif	/* _CHASH_H */

