//
//  util_thread.cpp
//  Classes for creating threads to offload work
//
//  Created by Ryan Sheffer on 11/24/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "allhead.h"
#include "util_thread.h"

namespace Threading {
    
    //--------------------------------------------------------------------------
    /**
     * The thread entry and exit. The thread will continue to run until either
     * a termination command is recieved from the thread arbiter or the worker
     * has requested termination because of error or finished work.
     */
    void *Thread::ThreadEntry(void *pClass)
    {
        Thread *pThreadClass = (Thread *)pClass;
        
        printf("Worker Thread %d Started\n", pThreadClass->m_iThreadID);
        
        while(true)
        {
            pthread_mutex_lock(&pThreadClass->m_threadMutex);
            
            // First check if we are suppose to terminate execution
            if(pThreadClass->m_bTerminate)
            {
                break;
            }
            
            // Do whatever job is nessesary
            if(pThreadClass->m_pWork)
            {
                thread_work_message msg =
                    pThreadClass->m_pWork->Run(pThreadClass->m_iThreadID);
                
                if(msg == THREAD_MSG_TERMINATE)
                {
                    pThreadClass->m_bTerminate = true;
                    printf("Thread %d terminated by worker class!\n",
                           pThreadClass->m_iThreadID);
                    break;
                }
            }
            
            pthread_mutex_unlock(&pThreadClass->m_threadMutex);
        }
        
        pthread_mutex_unlock(&pThreadClass->m_threadMutex);
        printf("Thread %d Terminated!\n", pThreadClass->m_iThreadID);
        pthread_exit(NULL);
    }
    
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    /**
     * A pointer to the global singleton thread arbiter.
     */
    ThreadArbiter *_pThreadArbiter = NULL;
    
    //--------------------------------------------------------------------------
    /**
     * Initializes the thread arbiter for future usage. Must be called before
     * any other ThreadArbiter methods can be called safely.
     */
    void ThreadArbiter::Initialize(void)
    {
        if(_pThreadArbiter == NULL)
        {
            _pThreadArbiter = new ThreadArbiter();
        }
    }
    
    //--------------------------------------------------------------------------
    /**
     * Creates a new thread under arbiter watch and guidance, and returns true
     * if the thread was successfully created.
     */
    bool ThreadArbiter::CreateNewThread(iThreadWork *pWork)
    {
        ASSERTION(_pThreadArbiter, "Trying to use the thread arbiter to create"
                                    "a thread, but the arbiter wasn't initialized!");
        
        return _pThreadArbiter->m_test.Start(&_pThreadArbiter->threadAttribs, pWork);
    }
    
    //--------------------------------------------------------------------------
    /**
     * This joins all threads to the parent thread, which means the
     * program will be blocked until all threads finish work.
     */
    void ThreadArbiter::JoinAllThreads(void)
    {
        ASSERTION(_pThreadArbiter, "Trying to use the thread arbiter to join"
                  "all threads, but the arbiter wasn't initialized!");
        
        _pThreadArbiter->m_test.JoinToParent();
    }
    
    
} // namespace Utility

