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

/** Pool of strings */
class CStringPool
{
public:
    
    CStringPool(const char *pszPoolName, iMemoryAllocator *allocator);
    
    CString AllocateString(const char *pszString);
    
    iMemoryAllocator *m_allocator;
};
    
} // namespace Utility

#endif // STRING_POOL_H
