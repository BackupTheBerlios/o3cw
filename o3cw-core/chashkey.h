// 
// File:   chashkey.h
// Author: alex
//
// Created on 23 Апрель 2008 г., 22:48
//

#ifndef _CHASHKEY_H
#define	_CHASHKEY_H

#include "ccrypto.h"

namespace o3cw
{
    class CHashKey: public o3cw::CThreadSafeObject
    {
    public:
        CHashKey(){};
        CHashKey(std::string &md5data)
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
        virtual ~CHashKey(){};
        bool operator<(const CHashKey& cmp) const
        {
            mlock.Lock();
            cmp.mlock.Lock();
            int i=0;
            while (i<3)
            {
                if (cmp.p[i]>p[i])
                {
                    cmp.mlock.UnLock();
                    mlock.UnLock();
                    return true;
                }
                else if(cmp.p[i]<p[i])
                {
                    cmp.mlock.UnLock();
                    mlock.UnLock();
                    return false;
                }
                i++;
            }
            cmp.mlock.UnLock();
            mlock.UnLock();
            return false;
        }
        CHashKey &operator=(const CHashKey& v)
        {
            mlock.Lock();
            memcpy(p, v.p, sizeof(p));
            o3cw::CCrypto::Base64Encode((const unsigned char*)p, sizeof(p),base64_value);
            mlock.UnLock();
            return *this;
        }
        std::string &GetBase64Value(std::string &buff) const
        {
            mlock.Lock();
            buff=base64_value;
            mlock.UnLock();
            return buff;
        }
    private:
        std::string base64_value;
        long long p[3];
    };
}

#endif	/* _CHASHKEY_H */

