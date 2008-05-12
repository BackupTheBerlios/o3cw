// 
// File:   cbreak.h
// Author: alex
//
// Created on 15 Февраль 2008 г., 23:06
//

#ifndef _cbreak_H
#define	_cbreak_H

#include <vector>
//#include "cjob.h"
#include <semaphore.h>
#include <sys/types.h>

#include "clock.h"

#define CBREAK_DESTROYED 1

namespace bonbon
{
    class CBreak: public bonbon::CLock
    {
        public:
            CBreak();
            ~CBreak();
            int Wait();
            int Run();
            int Destroy();
        private:
            bool destroyed;
    };
}

#endif	/* _cmodule_H */
