//
//  string_pool.h
//  script_testing
//
//  Created by Ryan Sheffer on 12/28/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef STRING_POOL_H
#define STRING_POOL_H

#ifdef _WIN
#pragma once
#endif

#include "util_string_allocation.h"

class iMemoryAllocator;

namespace Utility
{

//------------------------------------------------------------------------------
/** Pool of strings */
class CStringPool
{
public:
    
    CStringPool(const char *pszPoolName, iMemoryAllocator *allocator);
    
    
    CString Insert(const char *pszString, bool caseSensitive = false);
    CString Find(const char *pszString, bool caseSensitive = false);
    
    
private:
    /** A node containing a string or a number of strings if there were collisions */
    struct Node
    {
        const char *pString;
        Node *pNext;
    };
    
    Node *FindInternal(unsigned int hash, const char *pszString, bool caseSensitive = false);
    
    void Resize(unsigned int newSize);
    
    /** Nodes in buckets (linked list), see @Node */
    Node            **m_NodeBuckets;
    
    /** Number of nodes allocated */
    unsigned int    m_uiNumNodeBuckets;
    
    /** Number of nodes used */
    unsigned int    m_uiNumUsedNodeBuckets;
    
    /** The memory allocator assigned to this string table */
    iMemoryAllocator *m_allocator;
    
    const unsigned int INIT_NUM_BUCKETS = 29;
};
    
} // namespace Utility

#endif // STRING_POOL_H
