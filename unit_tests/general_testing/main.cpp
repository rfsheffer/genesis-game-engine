//
//  main
//  Testing Class
//
//  Created by Ryan Sheffer on 11/17/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../utilities/util_thread.h"

#define NUM_THREADS  3
#define MAX_OPS     40

struct operation
{
    int op1;
    int op2;
};

// Memory Pool Pointer
byte *pDataBank;

// Operation positions into the memory pool
operation *pStart;
operation *pEnd;
operation *pCur;

// Worker thread current operations
operation *pAssignedWork[NUM_THREADS];

pthread_mutex_t opWork_mutex[NUM_THREADS];
pthread_cond_t work_cnd[NUM_THREADS];

// Main worker thread mutex
pthread_mutex_t worker_thread_mutex;

// Control flags for terminating worker threads
bool        terminateThread[NUM_THREADS];



//------------------------------------------------------------------------------
/**
 * A worker threads set of instructions for dealing with requested operations
 */
void *opWorker(void *t)
{
    int thread_id = *(int*)t;
    
    printf("Worker Thread %d Started\n", thread_id);
    pthread_mutex_lock(&opWork_mutex[thread_id]);
    
    while(true)
    {
        printf("Thread %d waiting...\n", thread_id);
        
        // Wait for work to come down the line
        pthread_cond_wait(&work_cnd[thread_id], &opWork_mutex[thread_id]);
        
        // First check if we are suppose to terminate execution
        if(terminateThread[thread_id])
        {
            break;
        }
        
        if(pAssignedWork[thread_id])
        {
            int result = pAssignedWork[thread_id]->op1 + pAssignedWork[thread_id]->op2;
            printf("Thread %d solved and returned %d\n", thread_id, result);
        }
        
        pAssignedWork[thread_id] = NULL;
    }
    
    pthread_mutex_unlock(&opWork_mutex[thread_id]);
    printf("Worker Thread %d Terminating!\n", thread_id);
    pthread_exit(NULL);
}

//------------------------------------------------------------------------------
/**
 * Assigns work to the worker threads
 */
void *workAssigner(void *t)
{
    printf("Work Assignment Thread Started\n");
    size_t numOps = 0;
    do
    {
        pthread_mutex_lock(&worker_thread_mutex);
        
        numOps = (pCur - pStart);
        if(numOps != 0)
        {
            for(int i = 0; i < NUM_THREADS; ++i)
            {
                if(numOps == 0)
                {
                    break;
                }
                
                int mutexLocked = 0;
                
                if(pAssignedWork[i] == NULL && (mutexLocked = pthread_mutex_trylock(&opWork_mutex[i])) == 0)
                {
                    pAssignedWork[i] = --pCur;
                    --numOps;
                    
                    // Tell the worker it can do some work now
                    pthread_cond_signal(&work_cnd[i]);
                    pthread_mutex_unlock(&opWork_mutex[i]);
                }
                
                if(mutexLocked)
                {
                    printf("Waiting to Lock thread %d\n", i);
                }
            }
        }
        
        pthread_mutex_unlock(&worker_thread_mutex);
    }
    while(numOps != 0);
    
    printf("Work Assignment Thread Terminating!\n");
    pthread_exit(NULL);
}

using namespace Utility;

class WorkerTest : public iThreadWork
{
public:
    WorkerTest() : numIterations(0) {}
    
    thread_work_message Run(unsigned int threadID)
    {
        printf("doing something\n");
        ++numIterations;
        
        if(numIterations == 3)
        {
            return THREAD_MSG_TERMINATE;
        }
        
        return THREAD_MSG_CONTINUE;
    }
    
    int numIterations;
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    ThreadArbiter::Initialize();
    
    WorkerTest work;
    if(ThreadArbiter::CreateNewThread(&work))
    {
        ThreadArbiter::JoinAllThreads();
    }
    
    
    //CreateWorkerThread(workerTest);
    
    /*
    // Allocate memory pool for operations
    pDataBank = (byte *)malloc(sizeof(operation) * MAX_OPS);
    
    // Set pointers to place operations
    pStart = (operation *)pDataBank;
    pCur = (operation *)pDataBank;
    pEnd = pStart + MAX_OPS;
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_mutex_init(&worker_thread_mutex, NULL);
    pthread_mutex_lock(&worker_thread_mutex);
    
    // Initialize Mutexes and conditions
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        terminateThread[i] = false;
        pthread_mutex_init(&opWork_mutex[i], NULL);
        pthread_cond_init(&work_cnd[i], NULL);
    }
    
    pthread_t workAssignThread;
    pthread_create(&workAssignThread, &attr, workAssigner, (void *)NULL);
    
    int thread_id[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        thread_id[i] = i;
        pthread_create(&threads[i], &attr, opWorker, (void *)&thread_id[i]);
    }
    
    //while(1)
    {
        int countTo = 8;//rand() % 15 + 5;
        printf("Adding %d jobs\n", countTo);
        for(int i = 0; i < countTo; ++i)
        {
            if(pCur == pEnd)
            {
                break;
            }
            
            pCur->op1 = rand() % 100;
            pCur->op2 = rand() % 100;
            ++pCur;
        }
        //sleep(2);
    }
    
    printf("work added!\n");
    pthread_mutex_unlock(&worker_thread_mutex);
    
    // Wait for the work to be finished
    printf("waiting for work to be finished...\n");
    pthread_join(workAssignThread, NULL);
    
    printf("work finished, terminating workers:\n");
    // signal all work threads to terminate
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_mutex_lock(&opWork_mutex[i]);

        // Set the termination flag
        terminateThread[i] = true;
        
        // Signal the worker to start thinking again
        pthread_cond_signal(&work_cnd[i]);
        
        // Unlock so it can continue
        pthread_mutex_unlock(&opWork_mutex[i]);
        
        // Wait for the thread to terminate itself
        printf("waiting for thread %d to be finished...\n", i);
        pthread_join(threads[i], NULL);
    }
    
    // Clean up
    pthread_attr_destroy(&attr);
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_mutex_destroy(&opWork_mutex[i]);
        pthread_cond_destroy(&work_cnd[i]);
    }
    
    free(pDataBank);
    pDataBank = NULL;
    
    printf("DONE!\n");
    
    //pthread_exit(NULL);
     */
    return 0;
}



