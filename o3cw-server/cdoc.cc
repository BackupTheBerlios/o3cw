#include "cdoc.h"
#include "cclient.h"
#include "cdiff.h"

o3cw::CDoc::CDoc()
{
    
}

o3cw::CDoc::~CDoc()
{
    
}

int o3cw::CDoc::Open(o3cw::CClient &user)
{
    return 0;
}

int o3cw::CDoc::Close(o3cw::CClient &user)
{
    return 0;
}

int o3cw::CDoc::GetDiff(o3cw::CDiff &diff)
{
    return 0;
}

int o3cw::CDoc::CommitDiff(o3cw::CDiff &diff)
{
    return 0;
}

int o3cw::CDoc::GetXMLData(std::string &buff)
{
    return 0;
}

int o3cw::CDoc::CommitXMLData(std::string &buff)
{
    return 0;
}
