//
//  util_thread.h
//  Classes for creating threads to offload work
//
//  Created by Ryan Sheffer on 11/24/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_THREAD_H
#define UTIL_THREAD_H

#ifdef _WIN
#pragma once
#endif

#include <pthread.h>

namespace Threading {
    
    /** Messages returned by a thread worker class */
    enum thread_work_message
    {
        THREAD_MSG_CONTINUE,
        THREAD_MSG_TERMINATE,
    };
    
    //--------------------------------------------------------------------------
    /**
     * The class to inherret from for creating a new threaded routine.
     */
    class iThreadWork
    {
    public:
        virtual thread_work_message Run(unsigned int threadID) = 0;
    };
    
    //--------------------------------------------------------------------------
    /**
     * Generic thread
     */
    class Thread
    {
    public:
        
        /** Constructor */
        Thread()
        {
            m_bTerminate = false;
            pthread_mutex_init(&m_threadMutex, NULL);
        }
        
        ~Thread()
        {
            pthread_mutex_destroy(&m_threadMutex);
        }
        
        /** 
         * Returns true if the thread was successfully started, false if there
         * was an error starting the thread.
         */
        bool Start(pthread_attr_t *attribs, iThreadWork *pWork)
        {
            m_pWork = pWork;
            return (pthread_create(&m_hThread, attribs, ThreadEntry, this) == 0);
        }
        
        /**
         * Joins this thread to the parent process, causing the parent to be
         * blocked until this thread finishes. Note that this only works on
         * systems which support thread joining. Check your platform.
         */
        bool JoinToParent(void)
        {
            return pthread_join(m_hThread, NULL) == 0;
        }
        
        /**
         * Begins trying to lock the thread, blocking the calling process until
         * a lock is successfully made. Returns true when the lock is made.
         */
        bool Lock(void)
        {
            return pthread_mutex_lock(&m_threadMutex) == 0;
        }
        
        /**
         * Tries to lock the mutex, returns true if a lock was made.
         * Does not block the calling process.
         */
        bool TryLock(void)
        {
            return pthread_mutex_trylock(&m_threadMutex) == 0;
        }
        
        /**
         * Unlocks the mutex if it is locked, and returns true if unlock was
         * successfull.
         */
        bool Unlock(void)
        {
            return pthread_mutex_unlock(&m_threadMutex) == 0;
        }
        
        /**
         * Thread controlling mutex. When the thread is doing work, this will
         * be locked. Try not to lock this if possible, find ways of queing data
         * to the thread instead.
         */
        pthread_mutex_t m_threadMutex;
        
    private:
        
        /** Where the thread starts and ends */
        static void *ThreadEntry(void *pClass);
        
        /** The work for this thread to perform */
        iThreadWork     *m_pWork;
        
        /** The thread itself */
        pthread_t       m_hThread;
        
        /** The guid of this thread */
        int             m_iThreadID;
        
        /** Used to tell the thread it should terminate */
        bool            m_bTerminate;
    };
    
    //--------------------------------------------------------------------------
    /**
     * A class given power to control execution of threads.
     */
    class ThreadArbiter
    {
    public:
        
        /** Initialize the thread arbiter */
        static void Initialize(void);
        
        /** Create a new thread to do the work of a worker class */
        static bool CreateNewThread(iThreadWork *pWork);
        
        /** 
         * This joins all threads to the parent thread, which means the
         * program will be blocked until all threads finish work.
         */
        static void JoinAllThreads(void);
        
    private:
        
        /** Constructor Singlton */
        ThreadArbiter()
        {
            pthread_attr_init(&threadAttribs);
            pthread_attr_setdetachstate(&threadAttribs, PTHREAD_CREATE_JOINABLE);
        }
        
        // TODO: Container class for query goes here
        Thread   m_test;
        
        pthread_attr_t threadAttribs;
        
    };
    
} // namespace Utility

#endif // UTIL_THREAD_H
