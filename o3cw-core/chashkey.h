// 
// File:   chashkey.h
// Author: alex
//
// Created on 23 Апрель 2008 г., 22:48
//

#ifndef _CHASHKEY_H
#define	_CHASHKEY_H

namespace o3cw
{
    class CHashKey
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
        }
        virtual ~CHashKey(){};
        bool operator<(const CHashKey& cmp) const
        {
            int i=0;
            while (i<3)
            {
                if (cmp.p[i]>p[i])
                    return true;
                else if(cmp.p[i]<p[i])
                    return false;
                i++;
            }
            return false;
        }
        CHashKey &operator=(const CHashKey& v)
        {
            memcpy(p, v.p, sizeof(p));
            return *this;
        }
    private:
        long long p[3];
    };
}

#endif	/* _CHASHKEY_H */

