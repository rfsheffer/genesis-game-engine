//
//  memory_bucket.h
//  Memory Bucket Allocator
//
//  Created by Ryan Sheffer on 1/22/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef MEMORY_BUCKET_H
#define MEMORY_BUCKET_H

#ifdef _WIN
#pragma once
#endif

#include "memory_pool.h"

//------------------------------------------------------------------------------
/**
 * Memory Bucket
 */
struct MemoryBucket
{
    unsigned int    m_uiNumBlocks;
    size_t          m_uiBlockSize;
    
#ifdef _DEBUG
    alloc_info      *m_infos;
    unsigned int    m_uiNumInfos;
#endif
    
    byte            *m_pblocks;
    
    unsigned short  *m_pusIndexStack;
    unsigned short  m_pusStackIndex;
};

//------------------------------------------------------------------------------
/**
 * Bucket Memory Allocation:
 * Bucket memory allocation is the process of storing memory in like sized
 * buckets. A number of buckets are created with different sizes and lengths,
 * and when an allocation is made, the bucket it would properly fit in is
 * selected and filled. Utlimately with a number of small allocations, this
 * helps reduce memory fragmentation because it removes the unknown factor of
 * spacing between memory allocations.
 */
class MemoryBucketAllocator : public iMemoryAllocator
{
public:
    MemoryBucketAllocator(unsigned int numBuckets,
                          MemoryBucket *pBuckets);
                          
    
    void *Allocate(unsigned int bytes);
    void Deallocate(void *pMemory);
    
private:
    
    void *AllocateToBucket(unsigned int index);
    
    bool GetBucketOccupiedByMemory(void *pMemory, unsigned int &indexOut);
    
    unsigned int GetBlockInBucketByMemory(void *pMemory, unsigned int uiBucket);
    
    /** The buckets */
    MemoryBucket    *m_pBuckets;
    unsigned int    m_uiNumBuckets;
};

#endif // MEMORY_BUCKET_H
