#include "cdocpart.h"
#include "cclient.h"
#include "ccommand.h"
#include "error.h"
#include "cdoc.h"

o3cw::CUniqueAux o3cw::CDocPart::diffs_unique_aux;
        
o3cw::CDocPart::CDocPart(o3cw::CDoc &parentdoc): o3cw::CDifferenced::CDifferenced(*this, diffs_unique_aux), m_parent_doc(parentdoc)
{
    
}

o3cw::CDocPart::~CDocPart()
{
    std::vector<o3cw::CDiff *>::iterator it;
    for (it=diffs.begin(); it<diffs.end(); it++)
        delete *it;
}

int o3cw::CDocPart::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out)
{
    int result=0;
    
    o3cw::CUser *user=cmd.GetClient().GetUser();
    
    if (user==NULL)
        return O3CW_ERR_DENIED;
    
    if (cmd.CmdAviable())
    {
        std::string &c1=cmd.Pop();
        if (c1=="diff")
        {
            if (cmd.CmdAviable())
            {
                std::string &c2=cmd.Pop();
                if (c2=="id")
                {
                    if (cmd.CmdAviable())
                    {
                        std::string &c_id=cmd.Pop();
                        std::vector<o3cw::CDiff *>::iterator search_it;
                        for (search_it=diffs.begin(); search_it<diffs.end(); search_it++)
                        {
                            o3cw::CDiff *diff=*search_it;
                            std::string cur_key;
                            if (diff!=NULL && diff->GetKey().GetBase64Value(cur_key)==c_id)
                            {
                                std::string &c_do=cmd.Pop();
                                if (c_do=="do")
                                {
                                    result=diff->ExecCommand(cmd, cmd_out);
                                }
                                else
                                    result=O3CW_ERR_BAD_SEQ;
                            }
                        }
                    }
                }
                else if (c1=="commit")
                {
                    if (cmd.CmdAviable())
                    {
                        std::string &diff_data=cmd.Pop();
                        std::string md5buff;
                        o3cw::CCrypto::MD5HashHex(diff_data, md5buff);
                        o3cw::CHash diff_key(md5buff);
                        result=AddDiff(diff_data, diff_key, *user);
                    }
                    else
                        result=O3CW_ERR_BAD_SEQ;
                }
                else
                    result=O3CW_ERR_CMD_UNKNOWN;
            }
            else
                result=O3CW_ERR_BAD_SEQ;
        }
        else
            result=O3CW_ERR_CMD_UNKNOWN;
    }
    else
        result=O3CW_ERR_BAD_SEQ;
    
    return result;
}

int o3cw::CDocPart::RemoveClientFromMulticast(const o3cw::CClient &client)
{
    mlock.Lock();
    std::vector<o3cw::CDiff *>::iterator search_it;
    for (search_it=diffs.begin(); search_it<diffs.end(); search_it++)
    {
	(*search_it)->RemoveClientFromMulticast(client);
    }
    mlock.UnLock();
    return 0;
}
