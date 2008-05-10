#include "cdocpart.h"
#include "ccommand.h"
#include "error.h"
#include "cdoc.h"

o3cw::CUniqueAux o3cw::CDocPart::diffs_unique_aux;
        
o3cw::CDocPart::CDocPart(o3cw::CDoc &parentdoc): o3cw::CIdsObject::CIdsObject(diffs_unique_aux), m_parent_doc(parentdoc)
{
    
}

o3cw::CDocPart::~CDocPart()
{
    std::vector<o3cw::CDiff *>::iterator it;
    for (it=diffs.begin(); it<diffs.end(); it++)
        delete *it;
}

o3cw::ids o3cw::CDocPart::AddDiff(o3cw::CClient &client, std::string &buff)
{
    /* Parsing buff here... */
    
    /* Done, add new diff */
    
//    o3cw::CDiff *new_diff=new o3cw::CDiff(client, GetId(), diffs_unique_aux);
  //  diffs.push_back(new_diff);
    return 0;
}

int o3cw::CDocPart::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out)
{
    int result=0;
    
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
                        if (diff_data.length()>0)
                        {
                            bool already_exists=false;
                            std::string key;
                            o3cw::CCrypto::Base64Encode((const unsigned char *)diff_data.c_str(), diff_data.length(), key);
                            
                            std::vector<o3cw::CDiff *>::iterator search_it;
                            for (search_it=diffs.begin(); !already_exists && search_it<diffs.end(); search_it++)
                            {
                                o3cw::CDiff *diff=*search_it;
                                std::string cur_key;
                                if (diff!=NULL && diff->GetKey().GetBase64Value(cur_key)==key)
                                    already_exists=true;
                            }
                            
                            if (already_exists)
                            {
                                /* Error - this diff alreay commited */
                                result=O3CW_ERR_DUBLICATE;
                            }
                            else
                            {
                                /* Add new diff */
                                o3cw::CDiff *new_diff=new o3cw::CDiff(diff_data, key, *this);
                                
                                if (new_diff!=NULL)
                                    diffs.push_back(new_diff);
                                else
                                    result=O3CW_ERR_OUT_OF_MEM;
                            }
                        }
                        else
                        {
                            /* Error - empty diff */
                            result=O3CW_ERR_DATA_EMPTY;
                        }
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
