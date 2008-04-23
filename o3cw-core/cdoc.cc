#include <fstream>

#include "cdoc.h"
#include "cclient.h"
#include "cdiff.h"
#include "error.h"
#include "ccommand.h"

o3cw::CUniqueAux o3cw::CDoc::unique_data;

o3cw::CDoc::CDoc(): o3cw::CIdsObject::CIdsObject(o3cw::CDoc::unique_data)
{
    o3cw::ids parts_current_id=0;
    
    /* Every document contains at least one part - create it */
    o3cw::CDocPart *new_part=new o3cw::CDocPart(parts_unique_aux);
    parts.push_back(new_part);
}

o3cw::CDoc::~CDoc()
{
    /* Clean up all diffs */
    std::vector<o3cw::CDocPart *>::iterator it;
    for (it=parts.begin(); it!=parts.end(); it++)
        delete *it;
}

int o3cw::CDoc::OpenFile(const char *filename)
{
    int result=O3CW_ERR_BAD_FILE;
    std::ifstream is;
    is.open (filename, std::ios::binary);
    if (is.good())
    {
        is.seekg (0, std::ios::end);
        int length=is.tellg();
        is.seekg (0, std::ios::beg);
        char *buffer = new char [length];
        if (buffer!=NULL)
        {
            is.read (buffer,length);
            content.assign(buffer, length);
            delete [] buffer;
            result=0;
        }
        else
            result=O3CW_ERR_OUT_OF_MEM;
    }
    is.close();
    return result;
}

int o3cw::CDoc::GetData(CClient &client, std::string &buff)
{
    buff.assign(content);
    return 0;
}

int o3cw::CDoc::ExecCommand(o3cw::CCommand &cmd, o3cw::CCommand &cmd_out)
{
    std::string c;
    while (cmd.Pop(c)==0)
    {
        printf("next cmd in queue=[%s]\n", c.c_str());
        if (c=="get")
        {
            cmd_out.Push("get");
            cmd_out.Push(content.c_str());
        }
        else if (c=="load")
        {
            if (cmd.Pop(c)==0)
            {
                OpenFile(c.c_str());
            }
        }
    }
}
