//
//  memory_bucket.cpp
//  Memory Bucket Allocator
//
//  Created by Ryan Sheffer on 1/22/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "utilhead.h"
#include "memory_bucket.h"

//------------------------------------------------------------------------------
/**
 * Memory Bucket Allocator Constructor
 */
MemoryBucketAllocator::MemoryBucketAllocator(unsigned int numBuckets,
                                             MemoryBucket *pBuckets)
{
    m_pBuckets = pBuckets;
    m_uiNumBuckets = numBuckets;
}

//------------------------------------------------------------------------------
/**
 * Request memory from a bucket within the range of 'bytes'
 */
void *MemoryBucketAllocator::Allocate(unsigned int bytes, const char *pszFileName,
                                      unsigned int uiFileLine)
{
    for(unsigned int i = 0; i < m_uiNumBuckets; ++i)
    {
        if(m_pBuckets[i].m_uiBlockSize <= bytes)
        {
            return AllocateToBucket(i);
        }
    }
    
    // TODO: Feature to automatically resize buckets heap for new bucket size
    ASSERTION_ALWAYS("Unable to create a bucket allocation, no bucket found!");
    return NULL;
}

//------------------------------------------------------------------------------
/**
 * Request memory from a specific bucket
 */
void *MemoryBucketAllocator::AllocateToBucket(unsigned int index)
{
    // Get the bucket
    MemoryBucket &curBucket = m_pBuckets[index];
    
    // Get the unoccupied block
    unsigned int &usBlockIndex = curBucket.m_pusIndexStack[curBucket.m_pusStackIndex];
    if(usBlockIndex >= curBucket.m_uiNumBlocks)
    {
        // TODO: Feature to automatically resize buckets heap for new buckets
        ASSERTION_ALWAYS("Unable to create a bucket allocation, bucket is full!");
        return NULL;
    }
    
    // Get the block location
    byte *pBlockLoc = curBucket.m_pblocks + (curBucket.m_uiBlockSize * usBlockIndex);
    
    // We need to figure out where the next allocation will be. We use a stack
    // which keeps a list of "last empty slots". When an allocation is made here,
    // the stack is either popped to the last empty block, or the base stack
    // element is incremented (elements after will always be empty in that case)
    if(curBucket.m_pusStackIndex != 0)
    {
        --curBucket.m_pusStackIndex;
    }
    else
    {
        ++usBlockIndex;
    }
    
    return (void*)pBlockLoc;
}

//------------------------------------------------------------------------------
/**
 * Deallocate memory from buckets
 */
void MemoryBucketAllocator::Deallocate(void *pMemory)
{
    unsigned int bucketIndex;
    unsigned int blockIndex;
    
    if(!GetBucketOccupiedByMemory(pMemory, bucketIndex))
    {
        ASSERTION_ALWAYS("Tried to deallocate memory which doesn't exist in a bucket!");
        return;
    }
    
    blockIndex = GetBlockInBucketByMemory(pMemory, bucketIndex);

    ASSERTION(blockIndex < m_pBuckets[bucketIndex].m_uiNumBlocks,
              "Something went wrong with the bucket block dealloc. FIXME!");
    
    // Push an empty block index onto the stack
    MemoryBucket &bucket = m_pBuckets[bucketIndex];
    
    ++bucket.m_pusStackIndex;
    bucket.m_pusIndexStack[bucket.m_pusStackIndex] = blockIndex;
}

//------------------------------------------------------------------------------
/**
 * Gets the bucker for the allocation
 * @param pMemory The memory location to search for
 * @param indexOut The index of the bucket
 * @return false if the allocation wasn't found
 */
bool MemoryBucketAllocator::GetBucketOccupiedByMemory(void *pMemory, unsigned int &indexOut)
{
    for(unsigned int i = 0; i < m_uiNumBuckets; ++i)
    {
        MemoryBucket &bucket = m_pBuckets[i];
        
        if(bucket.m_pblocks >= pMemory &&
           pMemory < (bucket.m_pblocks + (bucket.m_uiNumBlocks * bucket.m_uiBlockSize)))
        {
            indexOut = i;
            return true;
        }
    }
    
    return false;
}

//------------------------------------------------------------------------------
/**
 * Gets the exact block of memory in a bucket from an address
 * @return The index
 */
unsigned int MemoryBucketAllocator::GetBlockInBucketByMemory(void *pMemory,
                                                     unsigned int uiBucket)
{
    ASSERTION(uiBucket < m_uiNumBuckets, "Invalid bucket to search blocks");
    MemoryBucket &bucket = m_pBuckets[uiBucket];
    
    size_t memOffset = (byte*)pMemory - bucket.m_pblocks;

    return (unsigned int)(memOffset / bucket.m_uiBlockSize);
}