//
//  memory_pool_interface.h
//  utilities
//
//  Created by Ryan Sheffer on 1/20/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef MEMORY_POOL_INTERFACE_H
#define MEMORY_POOL_INTERFACE_H

/**
 * The size of the pool for the entire application
 * TODO: This needs to be configurable.
 */
#define DEFAULT_POOL_SIZE       134217728

/**
 * The size of the general heap where all general allocations are made
 * TODO: This needs to be configurable as well
 */
#define GENERAL_HEAP_SIZE        67108864

/** Max pool name length */
#define POOL_NAME_LEN            32

#define NUM_ALLOCATOR_SLOTS     12

enum memory_allocator_types
{
    /**
     * This is just a general allocator. When an allocation is made, it is just
     * put right after the last allocation, no padding, no order.
     */
    UNORDERED_ALLOCATOR,
    
    /**
     * Allocations made with this allocator get put into blocks of a bucket.
     * This type of allocator is best for instances of many small allocations
     * which can easily cause fragmentation.
     */
    BUCKET_ALLOCATOR
};

/** Bucket information for creating a bucket allocator */
struct bucket_info
{
    unsigned int uiNumBlocks;
    unsigned int uiBlockSize;
};

//------------------------------------------------------------------------------
/** 
 * Allocation Information. These structures are assigned to all memory
 * allocations in debug mode.
 */
struct alloc_info
{
    char            *pszFileName;
    unsigned int    uiLine;
};

//------------------------------------------------------------------------------
/**
 * Interface for allocator class
 */
class iMemoryAllocator
{
public:
    virtual void *Allocate(unsigned int bytes) = 0;
    virtual void Deallocate(void *pMemory) = 0;
};

//------------------------------------------------------------------------------
/**
 * Interface for Master Memory Pool ( container of allocators )
 */
class iMemoryPool
{
public:
    
    virtual iMemoryAllocator *CreateBucketAllocator(const char *pszAllocatorName,
                                                    unsigned int numBuckets,
                                                    bucket_info *pBucketInfos) = 0;
    
    virtual iMemoryAllocator *CreateGeneralAllocator(const char *pszAllocatorName,
                                                     unsigned int numBytes) = 0;
    
    virtual void *TryAllocation(unsigned int uiNumBytes,
                                const char *pszFileName,
                                unsigned int uiFileLine) = 0;
};

#endif // MEMORY_POOL_INTERFACE_H
