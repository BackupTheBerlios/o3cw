#include <sys/syscall.h>
#include <algorithm>
#include "csemaphore.h"

#define PARALLEL_READERS 25

bonbon::CSemaphore::CSemaphore(): bonbon::CLock::CLock(PARALLEL_READERS)
{
    sem_init(&write_lock, 0,1);
    val=PARALLEL_READERS;
}

bonbon::CSemaphore::CSemaphore(unsigned int value): bonbon::CLock::CLock(value)
{
    sem_init(&write_lock, 0,1);
    val=value;
}

bonbon::CSemaphore::~CSemaphore()
{
    std::vector<pid_t>::iterator it;
    if (lockers_threads_soft.begin()!=lockers_threads_soft.end())
    {
        printf("CSemaphore %p destroyed, but some threads still are locking it for reading:\n", this);
        for (it=lockers_threads_soft.begin() ; it < lockers_threads_soft.end(); it++ )
        {
            printf(" * Thread id %i\n", *it);
        }
        printf("Looks like you forgotten to call UnLockRead() function somewhere.\n");
    }
    if (lockers_threads.begin()!=lockers_threads.end())
    {
        printf("CSemaphore %p destroyed, but some threads still are locking it for writing:\n", this);
        for (it=lockers_threads.begin() ; it < lockers_threads.end(); it++ )
        {
            printf(" * Thread id %i\n", *it);
        }
        printf("Looks like you forgotten to call UnLockWrite() function somewhere.\n");
    }
    
    sem_destroy(&write_lock);

}

int bonbon::CSemaphore::LockRead()
{
    bool not_w_locked=true;
    std::vector<pid_t>::iterator it;
    pid_t locker=syscall(SYS_gettid);
//    printf("Lock read by thread %i\n", locker);
    sem_wait(&self_lock);
    
    it=std::find(lockers_threads.begin(), lockers_threads.end(), locker);
    if (it!=lockers_threads.end())
    {
        not_w_locked=false;
//        printf("WARNING: Possible deadlock by thread %i in CSemaphore located at %p - unlock writing first\n", locker, this);
    }
    
    it=std::find(lockers_threads_soft.begin(), lockers_threads_soft.end(), locker);
    if (it!=lockers_threads_soft.end())
    {
        sem_post(&self_lock);
        printf("Possible read double lock by thread %i in CSemaphore located at %p\n", locker, this);
        return CSEMAPHORE_DRLOCK;
    }
    else
    {
        lockers_threads_soft.push_back(locker);
        sem_post(&self_lock);
        
        if (not_w_locked)
        {
            SoftLockRequire(locker);
            sem_wait(&lock);
            LockRegister(locker);
        }
    }
    return 0;
}

int bonbon::CSemaphore::UnLockRead()
{
    bool not_w_locked=true;
    std::vector<pid_t>::iterator it;
    pid_t locker=syscall(SYS_gettid);
//    printf("unLock read by thread %i\n", locker);
    sem_wait(&self_lock);
    
    it=std::find(lockers_threads.begin(), lockers_threads.end(), locker);
    if (it!=lockers_threads.end())
    {
        not_w_locked=false;
//        printf("WARNING: Can't unlock read int thread %i CSemaphore located at %p - unlock for writing first\n", locker, this);
    }
    it=std::find(lockers_threads_soft.begin(), lockers_threads_soft.end(), locker);
    
    if (it==lockers_threads_soft.end())
    {
        sem_post(&self_lock);
        printf("Possible double read unlock by thread %i in CSemaphore located at %p\n", locker, this);
        return CSEMAPHORE_DRUNLOCK;
    }
    else
    {
        lockers_threads_soft.erase(it);
        sem_post(&self_lock);
        
        if (not_w_locked)
        {
            sem_post(&lock);
            LockUnRegister(locker);
        }
    }
    return 0;
}

int bonbon::CSemaphore::LockWrite()
{
    std::vector<pid_t>::iterator it;
    pid_t locker=syscall(SYS_gettid);
//    printf("Lock write by thread %i\n", locker);
    
    sem_wait(&self_lock);
    it=std::find(lockers_threads_soft.begin(), lockers_threads_soft.end(), locker);
    
    if (it!=lockers_threads_soft.end())
    {
        sem_post(&self_lock);
        printf("Possible self-deadlock write by thread %i in CSemaphore located at %p - unlock read first\n", locker, this);
        return CSEMAPHORE_DWLOCK;
    }

    it=std::find(lockers_threads.begin(), lockers_threads.end(), locker);
    
    if (it!=lockers_threads.end())
    {
        sem_post(&self_lock);
        printf("Possible double write lock by thread %i in CSemaphore located at %p\n", locker, this);
        return CSEMAPHORE_DWLOCK;
    }
    else
    {
        lockers_threads.push_back(locker);
        sem_post(&self_lock);
        
        HardLockRequire(locker);
        sem_wait(&write_lock);
        for (unsigned int i=0; i<val; i++)
            sem_wait(&lock);
        sem_post(&write_lock);
        LockRegister(locker);
       
    }
   
   return 0;
}

int bonbon::CSemaphore::UnLockWrite()
{
    std::vector<pid_t>::iterator it;
    pid_t locker=syscall(SYS_gettid);
//    printf("unLock write by thread %i\n", locker);
    sem_wait(&self_lock);
    it=std::find(lockers_threads.begin(), lockers_threads.end(), locker);
    
    if (it==lockers_threads.end())
    {
        sem_post(&self_lock);
        printf("Possible write double unlock by thread %i in CSemaphore located at %p\n", locker, this);
        return CSEMAPHORE_DWUNLOCK;
        
    }
    else
    {
        lockers_threads.erase(it);
        sem_post(&self_lock);
        
        LockUnRegister(locker);
        for (unsigned int i=0; i<val; i++)
            sem_post(&lock);
    }
   
    return 0;
}
