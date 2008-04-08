// 
// File:   types.h
// Author: alex
//
// Created on 5 Апрель 2008 г., 7:20
//

#ifndef _TYPES_H
#define	_TYPES_H

namespace o3cw
{
    //Change this value if you change ids type properly!!!
    #define O3CW_MAX_IDS_VALUE 4294967295u
    
    //Type for numeric ids (clients, users, documents, parts, diffs...)
    typedef unsigned int ids;
    
    //Type for store POSIX time as number
    typedef long long time;
}

#endif	/* _TYPES_H */

