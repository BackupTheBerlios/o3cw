// 
// File:   cthread.h
// Author: alex
//
// Created on 15 Февраль 2008 г., 22:31
//

#ifndef _cthread_H
#define	_cthread_H

#include <pthread.h>
#include <semaphore.h>

namespace bonbon
{
//    void *ThreadExec(void *data);
    class CThread
    {
        public:
            friend void *ThreadExec(void *data);
            CThread();
            ~CThread();
            pid_t GetID();
            bool Running();
            bool Finished();
            bool Killed();
            void Kill();
            int Run();
            int Join();
            virtual int ThreadExecute();
        private:
            bool killed;
            sem_t self_lock;
            void SetThreadId(pid_t t_id);
            pthread_t thread;
            pid_t thread_id;
            bool finished;
            bool running;
            void Finish();
    };
}

#endif	/* _cthread_H */

