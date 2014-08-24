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
    
//------------------------------------------------------------------------------
/**
 * String Pool Constructor
 * @param pszPoolName The name of the pool
 * @param allocator The memory allocator used to store the strings. NULL to use
 *                  a default allocator (Not recommended).
 */
CStringPool::CStringPool(const char *pszPoolName, iMemoryAllocator *allocator)
{
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
}

//------------------------------------------------------------------------------
/** 
 * Allocate a new string or return an already existing string
 * @param pszString The string to allocate into a string pool string.
 */
CString CStringPool::AllocateString(const char *pszString)
{
    ASSERTION(pszString != NULL, "Trying to allocate a NULL string!");
    
    unsigned int stringlen = (unsigned int)strlen(pszString);
    char *pstrmem = (char *)m_allocator->Allocate(stringlen + 1, __FILE__, __LINE__);
    strncpy(pstrmem, pszString, stringlen);
    pstrmem[stringlen] = '\0';
    return CString(pstrmem);
}

} // namespace Utility