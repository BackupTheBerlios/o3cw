#include "cdoc.h"
#include "cclient.h"
#include "cdiff.h"

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
