// 
// File:   cjobmanager.h
// Author: alex
//
// Created on 8 Март 2008 г., 0:01
//

#ifndef _CJOBMANAGER_H
#define	_CJOBMANAGER_H

#include <queue>
#include <sys/types.h>

#include "cmutex.h"
#include "cthread.h"
#include "cbreak.h"

#define MAX_CJOBS_COUNT_IN_CJOBMANAGER 2147483647

namespace bonbon
{
    template <class J> class CJobManager
    {
        public:
            CJobManager()
            {
                jobs_tot=0;
                waiting_threads=0;
                sem_init(&self_lock, 0, 1);
                destroyed=false;
            }
            ~CJobManager()
            {
                
            }
            int PushJob(J &job)
            {
                sem_wait(&self_lock);
                if (jobs_tot<MAX_CJOBS_COUNT_IN_CJOBMANAGER)
                {
                    jobs_tot++;
                    jobs.push(job);
                    sem_post(&self_lock);
                    main_break.Run();
                    return 0;
                }
                sem_post(&self_lock);
                return -1;
            }
            J GetJob()
            {
                J result;
                sem_wait(&self_lock);
                if (jobs_tot>0)
                {
                    result=jobs.front();
                    jobs.pop();
                    jobs_tot--;
                }
                sem_post(&self_lock);
                return result;
            }
            int WaitForANewJob()
            {
                sem_wait(&self_lock);
                waiting_threads++;
                sem_post(&self_lock);
                main_break.Wait();
                sem_wait(&self_lock);
                waiting_threads--;
                sem_post(&self_lock);
                return 0;
            }
            int GetJobsCount()
            {
                int result;
                sem_wait(&self_lock);
                result=jobs_tot;
                sem_post(&self_lock);
                return result;
            }
            bool Destroyed()
            {
                sem_wait(&self_lock);
                bool result=destroyed;
                sem_post(&self_lock);
                return result;
            }
            void Destroy()
            {
                sem_wait(&self_lock);
                destroyed=true;
                sem_post(&self_lock);
                main_break.Destroy();
            }
            int LockQueue()
            {
                return queue_lock.Lock();
            }
            int UnLockQueue()
            {
                return queue_lock.UnLock();
            }
            unsigned int GetWaitingThreads()
            {
                unsigned int result;
                sem_wait(&self_lock);
                result=waiting_threads;
                sem_post(&self_lock);
                return result;
            }
        private:
            int jobs_tot;
            sem_t self_lock;
            bonbon::CMutex queue_lock;
            std::queue<J> jobs;
            bonbon::CBreak main_break;
            unsigned int waiting_threads;
            bool destroyed;
    };
}

#endif	/* _CJOBMANAGER_H */

