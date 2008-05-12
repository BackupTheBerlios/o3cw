// 
// File:   clock.h
// Author: alex
//
// Created on 7 Март 2008 г., 16:42
//

#ifndef _CLOCK_H
#define	_CLOCK_H

#include <sys/types.h>
#include <semaphore.h>

#include "slockgraph.h"

namespace bonbon
{
    class CLock
    {
    public:
	CLock();
        CLock(unsigned int lock_init_val);
        ~CLock();
        static int CLockInit();
    protected:
        int HardLockRequire(pid_t locker);
        int SoftLockRequire(pid_t locker);
        int LockRegister(pid_t locker);
        int LockUnRegister(pid_t locker);
	sem_t self_lock;
	std::vector<pid_t> lockers_threads;
	sem_t lock;
    private:
        static std::vector<bonbon::SLockGraph> locks_graph;
        static sem_t  locks_graph_lock;
        static int CheckLockGraph();
        static int RequireLock(pid_t transaction, bonbon::CLock *lock, int lock_mode);
        static int CatchLock(pid_t transaction, bonbon::CLock *lock);
        static int ReleaseLock(pid_t transaction, bonbon::CLock *lock);
	
    };
}

#endif	/* _CLOCK_H */

