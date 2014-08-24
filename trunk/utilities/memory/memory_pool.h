//
//  memory_pool.h
//  script_testing
//
//  Created by Ryan Sheffer on 1/18/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef MEMORY_POOL
#define MEMORY_POOL

#ifdef _WIN
#pragma once
#endif

#include "memory_interface.h"

/** Holds an allocator and its name */
struct allocator_holder
{
    iMemoryAllocator    *pAllocator;
    char                szName[POOL_NAME_LEN];
};

//------------------------------------------------------------------------------
/**
 * The primary Memory Pool
 */
class MemoryPool : public iMemoryPool
{
public:
    
    MemoryPool();
    ~MemoryPool();
    
    void Initialize(void);
    
    iMemoryAllocator *CreateBucketAllocator(const char *pszAllocatorName,
                                            unsigned int numBuckets,
                                            bucket_info *pBucketInfos);
    
    iMemoryAllocator *CreateGeneralAllocator(const char *pszAllocatorName,
                                             unsigned int numBytes);
    
    void *GeneralAllocation(unsigned int uiNumBytes,
                        const char *pszFileName,
                        unsigned int uiFileLine);
    
    void GeneralDeallocation(void *pMemory);
    
    /** A pointer to the base of the memory pool */
    byte        *m_pBase;
    
    /** A pointer to the end of the memory pool */
    byte        *m_pHead;
    
    /** A pointer to the MAIN allocation which covers this whole pool. It is
     * what you free when the pool is done. */
    void        *m_pPoolMemoryAllocation;
    
    /** The total size of this pool */
    size_t        m_uiTotalBytes;
    
    /** An allocator always availible for TryAllocation calls */
    iMemoryAllocator    *m_pGeneralAllocator;
    
    /** A list of allocators currently created */
    allocator_holder    *m_pAllocators;
    
    /** Max allocators */
    unsigned int        m_uiMaxAllocators;
    
    /** Number of allocators currently used */
    unsigned int        m_uiNumAllocators;
};

struct alloc_block
{
    /** The location in the memory of the allocation of this block */
    byte *pBlockMem;
    
    /** The size in bytes of this block */
    unsigned int uiBlockSize;
    
    /** Is this block being used */
    bool        bEmpty;
    
    /** The next block in line */
    alloc_block *pNext;
    
#ifdef _DEBUG
    /** Information about this allocation */
    alloc_info  info;
#endif
};

//------------------------------------------------------------------------------
/**
 * This is just a general allocator. When an allocation is made, it is just
 * put right after the last allocation, no padding, no order.
 */
class GeneralAllocator : public iMemoryAllocator
{
public:
    GeneralAllocator(unsigned int size, byte *pMemory);
    
    void *Allocate(unsigned int bytes,
                   const char *pszFileName,
                   unsigned int uiFileLine);
    
    void Deallocate(void *pMemory);
    
    /** A pointer to a linked list of blocks */
    alloc_block     *m_pBlocks;
    alloc_block     *m_pHeadBlock;
    
    /** This is the total size in bytes of the allocator */
    unsigned int    m_uiTotalSize;
    
    /** This is a pointer to the base of the memory for this allocator */
    byte            *m_pBase;
    
    /** This is the current location for brand new memory allocations */
    byte            *m_pHead;
};

#endif // MEMORY_POOL
