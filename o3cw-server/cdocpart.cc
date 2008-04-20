#include "cdocpart.h"

o3cw::CDocPart::CDocPart(o3cw::CUniqueAux &aux): o3cw::CIdsObject::CIdsObject(aux)
{

}

o3cw::CDocPart::~CDocPart()
{
    std::vector<o3cw::CDiff *>::iterator it;
    for (it=diffs.begin(); it!=diffs.end(); it++)
        delete *it;
}

o3cw::ids o3cw::CDocPart::AddDiff(o3cw::CClient &client, std::string &buff)
{
    /* Parsing buff here... */
    
    /* Done, add new diff */
    
    o3cw::CDiff *new_diff=new o3cw::CDiff(client, GetId(), diffs_unique_aux);
    diffs.push_back(new_diff);
}
