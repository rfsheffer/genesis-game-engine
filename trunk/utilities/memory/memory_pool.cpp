//
//  memory_pool.cpp
//  script_testing
//
//  Created by Ryan Sheffer on 1/18/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "allhead.h"
#include "memory_pool.h"
#include "memory_bucket.h"

//------------------------------------------------------------------------------
MemoryPool      g_MemoryPool;
iMemoryPool *GetMemoryPool(void)
{
    return &g_MemoryPool;
}

//------------------------------------------------------------------------------
MemoryPool::MemoryPool()
{
    m_uiTotalBytes = 0;
    m_uiNumAllocators = 0;
    m_uiMaxAllocators = 0;
    m_pBase = m_pHead = NULL;
    m_pPoolMemoryAllocation = NULL;
    m_pGeneralAllocator = NULL;
    m_pAllocators = NULL;
}

//------------------------------------------------------------------------------
MemoryPool::~MemoryPool()
{
    if(m_pPoolMemoryAllocation)
    {
        free(m_pPoolMemoryAllocation);
    }
}

/**
 * Initializes all default sub pools of the main pool
 */
void MemoryPool::Initialize(void)
{
    m_uiTotalBytes = DEFAULT_POOL_SIZE;
    m_uiNumAllocators = 0;
    m_uiMaxAllocators = NUM_ALLOCATOR_SLOTS;
    
    // Note: Memory pool related allocations should be kept sequential, so
    //       we are allocating the slots and the memory in one call.
    size_t allocatorBytes = sizeof(allocator_holder) * NUM_ALLOCATOR_SLOTS;
    m_pPoolMemoryAllocation = malloc(allocatorBytes + DEFAULT_POOL_SIZE);
    
    ASSERTION(m_pPoolMemoryAllocation, "Unable to allocate main memory pool!");
    
    m_pAllocators = (allocator_holder*)m_pPoolMemoryAllocation;
    
    m_pHead = m_pBase = (byte*)m_pPoolMemoryAllocation + allocatorBytes;
    
    // Always create a general allocator
    m_pGeneralAllocator = CreateGeneralAllocator("PrimaryHeap", GENERAL_HEAP_SIZE);
    
    bucket_info     stringBuckets[] = { { 20, 16 },
        { 20, 32 },
        { 20, 64 },
        { 10, 128 },
        { 10, 256 },
        { 10, 512 } };
    
    // testing buckets
    CreateBucketAllocator("test_buckets", ARRAYSIZE(stringBuckets), stringBuckets);
}

//------------------------------------------------------------------------------
/**
 * General Allocation
 */
iMemoryAllocator *MemoryPool::CreateBucketAllocator(const char *pszAllocatorName,
                                                    unsigned int numBuckets,
                                                    bucket_info *pBucketInfos)

{
    ASSERTION(m_uiNumAllocators != m_uiMaxAllocators,
              "Ran out of memory allocator slots");
    if(m_uiNumAllocators == m_uiMaxAllocators)
    {
        return NULL;
    }
    
    unsigned int numBytes = sizeof(MemoryBucket) * numBuckets;
    
    // Determine amount needed for buckets
    for(unsigned int i = 0; i < numBuckets; ++i)
    {
        numBytes +=
        pBucketInfos[i].uiNumBlocks * pBucketInfos[i].uiBlockSize;
        
        // Each bucket has a stack of shorts for quick hole filling.
        numBytes += sizeof(unsigned short) * pBucketInfos[i].uiNumBlocks;
    }
    
    if((m_uiTotalBytes - (m_pHead - m_pBase)) < numBytes)
    {
        return NULL;
    }
    
    MemoryBucket *pBuckets = (MemoryBucket *)m_pHead;
    m_pHead += sizeof(MemoryBucket) * numBuckets;
    
    // Populate Bucket info
    for(unsigned int i = 0; i < numBuckets; ++i)
    {
        pBuckets[i].m_uiBlockSize = pBucketInfos[i].uiBlockSize;
        pBuckets[i].m_uiNumBlocks = pBucketInfos[i].uiNumBlocks;
#ifdef _DEBUG
        pBuckets[i].m_infos = NULL;
        pBuckets[i].m_uiNumInfos = 0;
#endif
        
        // Assign memory for short stack
        pBuckets[i].m_pusStackIndex = 0;
        pBuckets[i].m_pusIndexStack = (unsigned short*)m_pHead;
        m_pHead += sizeof(unsigned short) * pBucketInfos[i].uiNumBlocks;
        
        pBuckets[i].m_pusIndexStack[0] = 0;
    }
    
    // Now assign the bucket blocks
    for(unsigned int i = 0; i < numBuckets; ++i)
    {
        pBuckets[i].m_pblocks = m_pHead;
        m_pHead += pBucketInfos[i].uiNumBlocks * pBucketInfos[i].uiBlockSize;
    }
    
    
    MemoryBucketAllocator *pAllocator = new MemoryBucketAllocator(numBuckets,
                                                                  pBuckets);
    
    m_pAllocators[m_uiNumAllocators].pAllocator = pAllocator;
    strncpy(m_pAllocators[m_uiNumAllocators].szName, pszAllocatorName, POOL_NAME_LEN);
    ++m_uiNumAllocators;
    return pAllocator;
}

//------------------------------------------------------------------------------
/**
 * General Allocation
 */
iMemoryAllocator *MemoryPool::CreateGeneralAllocator(const char *pszAllocatorName,
                                                    unsigned int numBytes)
{
    ASSERTION(m_uiNumAllocators != m_uiMaxAllocators,
              "Ran out of memory allocator slots");
    if(m_uiNumAllocators == m_uiMaxAllocators)
    {
        return NULL;
    }
    
    if((m_uiTotalBytes - (m_pHead - m_pBase)) < numBytes)
    {
        return NULL;
    }
    
    GeneralAllocator *pAllocator = new GeneralAllocator(numBytes, m_pHead);
    m_pHead += numBytes;
    
    m_pAllocators[m_uiNumAllocators].pAllocator = pAllocator;
    strncpy(m_pAllocators[m_uiNumAllocators].szName, pszAllocatorName, POOL_NAME_LEN);
    ++m_uiNumAllocators;
    return pAllocator;
}

//------------------------------------------------------------------------------
/**
 * Trys to make a general allocation in the general allocator.
 */
void *MemoryPool::TryAllocation(unsigned int uiNumBytes,
                                const char *pszFileName,
                                unsigned int uiFileLine)
{
    ASSERTION(m_pGeneralAllocator,
              "Trying to make a general allocation, but there"
              " is no general allocator!");
    
    // TODO: Use Bucket allocator for smaller allocations
    
    return m_pGeneralAllocator->Allocate(uiNumBytes);
}

//------------------------------------------------------------------------------
/**
 * General Allocation Constructor
 */
GeneralAllocator::GeneralAllocator(unsigned int size, byte *pMemory)
{
    m_pBase = m_pHead = pMemory;
    m_uiTotalSize = size;
    m_pBlocks = m_pHeadBlock = NULL;
}

//------------------------------------------------------------------------------
/**
 * Function for spliting a block on a 'bytes' boundary
 */
bool SplitMemoryBlock(alloc_block *pBlock, unsigned int bytes)
{
    // Same Size? no split needed
    if(pBlock->uiBlockSize == bytes)
    {
        return true;
    }
    
    // If there isn't enough room to make another block, we can't use this spot.
    if((pBlock->uiBlockSize - bytes) < sizeof(alloc_block))
    {
        return false;
    }
    
    // Create a new allocation block to cover the rest of the unused bytes
    alloc_block *pNewBlock = (alloc_block *)(pBlock->pBlockMem + bytes);
    pNewBlock->pNext = pBlock->pNext;
    pNewBlock->uiBlockSize = (pBlock->uiBlockSize - bytes) - sizeof(alloc_block);
    pNewBlock->bEmpty = true;
    pNewBlock->pBlockMem = (byte*)(pNewBlock + 1);
    pBlock->pNext = pNewBlock;
    
    return true;
}

//------------------------------------------------------------------------------
/**
 * General Allocation
 */
void *GeneralAllocator::Allocate(unsigned int bytes)
{
    // Look for a place in the current blocks
    alloc_block *pCurBlock = m_pBlocks;
    while(pCurBlock)
    {
        if(pCurBlock->bEmpty && pCurBlock->uiBlockSize >= bytes)
        {
            // Split the block if needed
            if(SplitMemoryBlock(pCurBlock, bytes))
            {
                return pCurBlock->pBlockMem;
            }
        }
        
        pCurBlock = pCurBlock->pNext;
    }
    
    size_t bytesLeft = m_uiTotalSize - (m_pHead - m_pBase);
    
    // Can't fit it anyway? Out of memory!
    if(bytesLeft < (bytes + sizeof(alloc_block)))
    {
        ASSERTION(false, "Ran out of memory for allocation in general memory pool!");
        return NULL;
    }
    
    // New block on the end
    alloc_block *pNewBlock = (alloc_block *)(m_pHead);
    pNewBlock->pNext = NULL;
    pNewBlock->bEmpty = false;
    pNewBlock->pBlockMem = (byte*)(pNewBlock + 1);
    pNewBlock->uiBlockSize = bytes;
    
    if(m_pHeadBlock)
    {
        m_pHeadBlock->pNext = pNewBlock;
    }
    if(m_pBlocks == NULL)
    {
        m_pBlocks = pNewBlock;
    }
    
    m_pHeadBlock = pNewBlock;
    
    return pNewBlock->pBlockMem;
}

//------------------------------------------------------------------------------
/**
 * Deallocate memory from general allocator
 */
void GeneralAllocator::Deallocate(void *pMemory)
{
    
}