//
//  string_pool.h
//  script_testing
//
//  Created by Ryan Sheffer on 12/28/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef STRING_POOL_H
#define STRING_POOL_H

#include "string_pointer.h"

/** Pool of strings */
class CStringPool
{
public:
    
    CStringPool(const char *pszPoolName);
    
    CStringPtr AllocateString(const char *pszString);
    
};

#endif // STRING_POOL_H
