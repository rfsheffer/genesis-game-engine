//
//  string_pool.cpp
//  script_testing
//
//  Created by Ryan Sheffer on 12/28/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "utilhead.h"
#include "util_string_pool.h"
#include "memory/memory_interface.h"

namespace Utility
{
    
    /**
     * A namespace containing the hashing method (XOR) used for this string pool.
     */
    namespace {
        bool    gHashLookupInit = false;
        byte    gHashLookup[256];
        
        /** Sets up a table tolower our individual characters */
        void InitHashLookup(void)
        {
            for(unsigned int i = 0; i < 256; ++i)
            {
                byte c = tolower(i);
                gHashLookup[i] = c * c;
            }
            
            gHashLookupInit = true;
        }
        
        /** Simple Hashing function for a string */
        unsigned int GetHash(const char *pszStr, unsigned int length)
        {
            ASSERTION(gHashLookupInit, "Trying to get a hash from a string but "
                                        "the lookup table hasn't been initialized!");
            ASSERTION(pszStr && pszStr[0] != '\0',
                      "Invalid string for string pool hash function!");
            ASSERTION(length, "Invalid string length passed into string pool hash!");
            
            unsigned int hash = 0;
            char c;
            while((c = *pszStr++) != 0 && length--)
            {
                // This is a simple and fast hashing algorithm which XORs each
                // character to the hash and shifts the bit each character.
                // Produces a varied hash.
                hash <<= 1;
                hash ^= gHashLookup[(int)c];
            }
            return hash;
        }
    } // empty namespace
    
//------------------------------------------------------------------------------
/**
 * String Pool Constructor
 * @param pszPoolName The name of the pool
 * @param allocator The memory allocator used to store the strings. NULL to use
 *                  a default allocator (Not recommended).
 */
CStringPool::CStringPool(const char *pszPoolName, iMemoryAllocator *allocator)
{
    if(!gHashLookupInit)
    {
        InitHashLookup();
    }
    
    iMemoryPool *pMemPool = GetMemoryPool();
    
    // We create a basic bucket allocator with some general settings if
    // no allocator explicitly set.
    if(allocator == NULL)
    {
        Logging::Warning("Creating a string pool with default allocator!\n");
        bucket_info buckets[] = {   // (num blocks)     (block size)
                                    {   20,             8    },
                                    {   20,             16   },
                                    {   40,             32   },
                                    {   40,             64   },
                                    {   40,             128   },
                                    {   40,             256   },
                                    {   40,             512   },
                                    {   30,             1024   },
                                    {   20,             2048   },
                                    {   10,             4096   }
                                };
        allocator = pMemPool->CreateBucketAllocator(pszPoolName,
                                                    ARRAYSIZE(buckets),
                                                    buckets);
    }
    
    m_allocator = allocator;
    
    // Allocate the node buckets
    m_NodeBuckets =
    (Node **)GetMemoryPool()->GeneralAllocation(INIT_NUM_BUCKETS * sizeof(Node *),
                                                               __FILE__,
                                                               __LINE__);
    for(unsigned int i = 0; i < INIT_NUM_BUCKETS; ++i)
    {
        m_NodeBuckets[i] = NULL;
    }
    m_uiNumNodeBuckets = INIT_NUM_BUCKETS;
    m_uiNumUsedNodeBuckets = 0;
}

//------------------------------------------------------------------------------
/** 
 * Allocate a new string or return an already existing string
 * @param pszString The string to allocate into a string pool string.
 */
CString CStringPool::Insert(const char *pszString, bool caseSensitive)
{
    ASSERTION(pszString != NULL, "Trying to allocate a NULL string!");
    
    Node **ppWalk, *pTemp;
    
    // Get the hash
    unsigned int hash = GetHash(pszString, UINT32_MAX);

    // Determine where we will place this string wrapping the hash with
    // the nodes array.
    ppWalk = &m_NodeBuckets[hash % m_uiNumNodeBuckets];
    
    // If the node is filled, determine if we found the same node
    // as the string, or if we should put this string in the linked list.
    while((pTemp = *ppWalk) != NULL)
    {
        // check case sensitivity
        if(caseSensitive && strcmp(pTemp->pString, pszString) == 0)
        {
            return CString(pTemp->pString);
        }
        else if(!caseSensitive && util_stricmp(pTemp->pString, pszString) == 0)
        {
            return CString(pTemp->pString);
        }
        ppWalk = &(pTemp->pNext);
    }
    
    // Add the new node element
    const char *pRetStr = NULL;
    if(!*ppWalk)
    {
        // Create a node to place in the linked list
        *ppWalk = (Node *)GetMemoryPool()->GeneralAllocation(sizeof(Node),
                                                           __FILE__,
                                                           __LINE__);
        
        // Allocate the new string in a bucket allocator
        // Strings are normally divisible by 2 so buckets are a sound choice,
        // and fragmentation is reduced.
        unsigned int stringlen = (unsigned int)strlen(pszString);
        char *pstrmem = (char *)m_allocator->Allocate(stringlen + 1, __FILE__, __LINE__);
        strncpy(pstrmem, pszString, stringlen);
        pstrmem[stringlen] = '\0';
        
        // Setup the node
        (*ppWalk)->pNext = NULL;
        (*ppWalk)->pString = (const char *)pstrmem;
        
        pRetStr = (*ppWalk)->pString;
        ++m_uiNumUsedNodeBuckets;
    }
    
    // Check if the number of strings added to the pool is greater than
    // double the number of node buckets. This is the tipping point for hash
    // efficiency and means we need to quadrupal the number of buckets to stay
    // efficient.
    if(m_uiNumUsedNodeBuckets > 2 * m_uiNumNodeBuckets)
    {
        Resize(4 * m_uiNumNodeBuckets - 1);
    }
    
    return CString(pRetStr);
}

//------------------------------------------------------------------------------
/**
 * Finds a string in the string pool and returns its pointer container.
 */
CString CStringPool::Find(const char *pszString, bool caseSensitive)
{
    ASSERTION(pszString != NULL, "Trying to allocate a NULL string!");
    unsigned int hash = GetHash(pszString, UINT32_MAX);
    Node *pTemp;
    if((pTemp = FindInternal(hash, pszString, caseSensitive)) != NULL)
    {
        return CString(pTemp->pString);
    }
    return NULL_STRING;
}
    
//------------------------------------------------------------------------------
/**
 * Add more node buckets. This happens when strings are added and hashing efficiency
 * has been reduced by too much and to get that back more buckets needs to be added.
 */
void CStringPool::Resize(unsigned int newSize)
{
    Node *pHead = NULL, *pWalk, *pTemp;
    unsigned int i;
    // reverse individual bucket lists
    // we do this because new strings are added at the end of bucket
    // lists so that case sens strings are always after their
    // corresponding case insens strings
    
    for (i = 0; i < m_uiNumNodeBuckets; i++) {
        pWalk = m_NodeBuckets[i];
        while (pWalk)
        {
            pTemp = pWalk->pNext;
            pWalk->pNext = pHead;
            pHead = pWalk;
            pWalk = pTemp;
        }
    }
    
    // Reallocate and re-initialize
    // TODO
    //m_NodeBuckets = (Node **) dRealloc(buckets, newSize * sizeof(Node));
    for (i = 0; i < newSize; i++)
    {
        m_NodeBuckets[i] = 0;
    }
    
    m_uiNumNodeBuckets = newSize;
    pWalk = pHead;
    while (pWalk)
    {
        unsigned int hash;
        pTemp = pWalk;
        
        pWalk = pWalk->pNext;
        hash = GetHash(pTemp->pString, UINT32_MAX);
        pTemp->pNext = m_NodeBuckets[hash % newSize];
        m_NodeBuckets[hash % newSize] = pTemp;
    }
}

//------------------------------------------------------------------------------
/**
 * Finds an already added node. This is for class usage only.
 */
CStringPool::Node *CStringPool::FindInternal(unsigned int hash, const char *pszString, bool caseSensitive)
{
    Node **ppWalk, *pTemp;
    
    // Determine where we will place this string wrapping the hash with
    // the nodes array.
    ppWalk = &m_NodeBuckets[hash % m_uiNumNodeBuckets];
    
    // If the node is filled, determine if we found the same node
    // as the string, or if we should put this string in the linked list.
    while((pTemp = *ppWalk) != NULL)
    {
        // check case sensitivity
        if(caseSensitive && strcmp(pTemp->pString, pszString) == 0)
        {
            return pTemp;
        }
        else if(!caseSensitive && util_stricmp(pTemp->pString, pszString) == 0)
        {
            return pTemp;
        }
        ppWalk = &(pTemp->pNext);
    }
    
    return NULL;
}

} // namespace Utility