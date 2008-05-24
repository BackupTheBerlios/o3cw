#include <sys/syscall.h>
#include <algorithm>
#include "cbreak.h"

bonbon::CBreak::CBreak(): bonbon::CLock::CLock(0)
{
    destroyed=false;
}

bonbon::CBreak::~CBreak()
{
    Destroy();
}

int bonbon::CBreak::Wait()
{
    sem_wait(&self_lock);
    
    if (destroyed)
    {
        sem_post(&self_lock);
        return CBREAK_DESTROYED;
    }
    
    pid_t locker=syscall(SYS_gettid);
    lockers_threads.push_back(locker);
    sem_post(&self_lock);
    
    sem_wait(&lock);
    
    sem_wait(&self_lock);
    std::vector<pid_t>::iterator it;    
    it=std::find(lockers_threads.begin(), lockers_threads.end(), locker);
    if (it!=lockers_threads.end())
        it=--lockers_threads.erase(it);
    
    if (destroyed)
    {
        sem_post(&self_lock);
        return CBREAK_DESTROYED;
    }
    
    sem_post(&self_lock);
    return 0;
}

int bonbon::CBreak::Run()
{
    sem_post(&lock);
    return 0;
}

int bonbon::CBreak::Destroy()
{
    sem_wait(&self_lock);
    if (destroyed)
    {
        sem_post(&self_lock);
        return CBREAK_DESTROYED;
    }
    else
    {
        destroyed=true;  
        std::vector<pid_t>::iterator it=lockers_threads.begin();
        while (it!=lockers_threads.end())
        {
            sem_post(&lock);
            it++;
        }
        sem_post(&self_lock);
        
    }
    return 0;
}
