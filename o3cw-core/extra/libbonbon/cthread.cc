#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "cthread.h"

namespace bonbon
{
    void *ThreadExec(void *data);
}

bonbon::CThread::CThread()
{
    sem_init(&self_lock, 0, 1);
    thread_id=0;
    finished=false;
    killed=false;
    running=false;
}

bonbon::CThread::~CThread()
{
         
}

void bonbon::CThread::Kill()
{
    sem_wait(&self_lock);
    killed=true;
    sem_post(&self_lock);
}

bool bonbon::CThread::Killed()
{
    bool result=false;
    sem_wait(&self_lock);
    if (killed)
        result=true;
    sem_post(&self_lock);
    return result;
}

bool bonbon::CThread::Running()
{
    bool result=false;
    sem_wait(&self_lock);
    if (running)
        result=true;
    sem_post(&self_lock);
    return result;
}

int bonbon::CThread::Join()
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

int bonbon::CThread::Run()
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

void bonbon::CThread::SetThreadId(pid_t t_id)
{
    sem_wait(&self_lock);
    thread_id=t_id;
    sem_post(&self_lock);
}

int bonbon::CThread::ThreadExecute()
{
    printf("Origin Thread\n");
    return 0;
}

void *bonbon::ThreadExec(void *data)
{
    if (data!=NULL)
    {
        bonbon::CThread *thread=(bonbon::CThread *) data;
        thread->SetThreadId(syscall(SYS_gettid));
        thread->ThreadExecute();
    }
    return NULL;
}

pid_t bonbon::CThread::GetID()
{
    return thread_id;
}

void bonbon::CThread::Finish()
{
    sem_wait(&self_lock);
    finished=true;
    sem_post(&self_lock);
}

bool bonbon::CThread::Finished()
{
    sem_wait(&self_lock);
    bool result=finished;
    sem_post(&self_lock);
    return result;
}
