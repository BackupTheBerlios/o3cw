#include <stdlib.h>
#include <sys/syscall.h>
/*
#include "cvthread.h"

namespace bonbon
{
    void *ThreadExec(void *data);
}

bonbon::CVThread::CVThread()
{
    sem_init(&self_lock, 0, 1);
    thread_id=0;
    finished=false;
    killed=false;
    running=false;
}

bonbon::CVThread::~CVThread()
{
         
}

void bonbon::CVThread::Kill()
{
    sem_wait(&self_lock);
    killed=true;
    sem_post(&self_lock);
}

bool bonbon::CVThread::Killed()
{
    bool result=false;
    int v=0;
    sem_wait(&self_lock);
    if (killed)
        result=true;
    sem_post(&self_lock);
    return result;
}

bool bonbon::CVThread::Running()
{
    bool result=false;
    sem_wait(&self_lock);
    if (running)
        result=true;
    sem_post(&self_lock);
    return result;
}

int bonbon::CVThread::Join()
{
    int result=0;
    sem_wait(&self_lock);
    if (running)
    {    
        sem_post(&self_lock);
        result=pthread_join(thread, NULL);
    }
    else
        sem_post(&self_lock);
    return result;
}

int bonbon::CVThread::Run()
{
    int result=0;
    sem_wait(&self_lock);
    if (!running)
    {
        result=pthread_create(&thread, NULL, &bonbon::ThreadExec, this);
        if (result==0)
            running=true;
    }
    sem_post(&self_lock);
    return result;
}

void bonbon::CVThread::SetThreadId(pid_t t_id)
{
    sem_wait(&self_lock);
    thread_id=t_id;
    sem_post(&self_lock);
}

int bonbon::CVThread::ThreadExecute()
{
    printf("Origin VThread\n");
    return 0;
}

void *bonbon::ThreadExec(void *data)
{
    if (data!=NULL)
    {
        bonbon::CVThread *thread=(bonbon::CVThread *) data;
        thread->SetThreadId(syscall(SYS_gettid));
        thread->ThreadExecute();
    }
    return NULL;
}

pid_t bonbon::CVThread::GetID()
{
    return thread_id;
}

void bonbon::CVThread::Finish()
{
    sem_wait(&self_lock);
    finished=true;
    sem_post(&self_lock);
}

bool bonbon::CVThread::Finished()
{
    sem_wait(&self_lock);
    bool result=finished;
    sem_post(&self_lock);
    return result;
}
*/
