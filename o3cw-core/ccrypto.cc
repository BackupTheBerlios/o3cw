#include <openssl/md5.h> 

#include "ccrypto.h"

int o3cw::CCrypto::MD5HashHex(std::string &data, std::string &buff)
{
    buff.erase();

    unsigned char md5digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)data.c_str(),data.length(), md5digest);

    for (int i=0;i<MD5_DIGEST_LENGTH;i++)
    {
        char tmps[10];
        snprintf(tmps,9, "%x",  md5digest[i]);
        buff+=tmps;
    }
    return 0;
}

int o3cw::CCrypto::MD5HashBin(std::string &data, std::string &buff)
{
    unsigned char md5digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)data.c_str(),data.length(), md5digest);
    buff.assign((char *)md5digest, MD5_DIGEST_LENGTH);
    return 0;
}

void o3cw::CCrypto::Base64Encode(const unsigned char* input,size_t l,std::string& output)
{
    output.erase();
    const char *bstr ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t i = 0;
    size_t o = 0;
    while (i < l)
    {
        size_t remain = l - i;
        switch (remain)
        {
        case 1:
            output += bstr[ ((input[i] >> 2) & 0x3f) ];
            output += bstr[ ((input[i] << 4) & 0x30) ];
            output += "==";
            break;
        case 2:
            output += bstr[ ((input[i] >> 2) & 0x3f) ];
            output += bstr[ ((input[i] << 4) & 0x30) + ((input[i + 1] >> 4) & 0x0f) ];
            output += bstr[ ((input[i + 1] << 2) & 0x3c) ];
            output += "=";
            break;
        default:
            output += bstr[ ((input[i] >> 2) & 0x3f) ];
            output += bstr[ ((input[i] << 4) & 0x30) + ((input[i + 1] >> 4) & 0x0f) ];
            output += bstr[ ((input[i + 1] << 2) & 0x3c) + ((input[i + 2] >> 6) & 0x03) ];
            output += bstr[ (input[i + 2] & 0x3f) ];
        }
        o += 4;
        i += 3;
    }
}

int o3cw::CCrypto::Base64Decode(const char *input, std::string &out)
{
    if (input==NULL)
            return -1;
    out.erase();
    int result=0;
    const char *bstr ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const char *ptr=input;
    for (unsigned int i=0;i<strlen(input); i+=4)
    {
        unsigned char outb[3];
        int left=strlen(input)-i;
        if (left>3)
            left=4;
        memset(outb, 0, 3);
        for (unsigned int k=0; k<left; k++)
        {
            for (unsigned int j=0; j<strlen(bstr); j++)
            {
                if (ptr[k]==bstr[j])
                {
                    if (k==0)
                    {
                        outb[0]=j;
                        outb[0]=outb[0]<<2;
                    }
                    else if (k==1)
                    {
                        outb[1]=j;
                        outb[1]=outb[1]<<2;
                        unsigned char t=outb[1];
                        t=t>>6;
                        outb[0]=outb[0] | t;
                        outb[1]=outb[1]<<2;
                        char tmp[2];
                        tmp[0]=outb[0]; tmp[1]=0;
                    }
                    else if (k==2)
                    {
                        outb[2]=j;
                        outb[2]=outb[2] << 2;
                        unsigned char t=outb[2]>>4;
                        outb[1]=outb[1] | t;
                        outb[2]=outb[2]<<4;
                    }
                    else if(k==3)
                    {
                        unsigned char t=j;
                        t=t>>2;
                        outb[2]=outb[2] | j;
                    }
                }
                else
                    result=-1;
            }
        }
        if (left>0)
            out.append((char *)outb, 3);
        ptr+=left;
    }
    return result;
}
