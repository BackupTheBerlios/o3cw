// 
// File:   cmutex.h
// Author: alex
//
// Created on 15 Февраль 2008 г., 22:32
//

#ifndef _cmutex_H
#define	_cmutex_H

#include <sys/types.h>
#include <semaphore.h>
#include <vector>
#include "clock.h"

#define CMUTEX_DUNLOCK 1
#define CMUTEX_DEADLOCK 2

namespace bonbon
{
    class CMutex: public CLock
    {
        public:
            CMutex();
            ~CMutex();
            int Lock();
            int UnLock();
    };
}

#endif	/* _cmutex_H */

