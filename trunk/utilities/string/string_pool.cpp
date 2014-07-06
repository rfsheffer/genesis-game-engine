//
//  string_pool.cpp
//  script_testing
//
//  Created by Ryan Sheffer on 12/28/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "utilhead.h"
#include "string_pool.h"

//------------------------------------------------------------------------------
/**
 * String Pool Constructor
 * @param pszPoolName The name of the pool
 */
CStringPool::CStringPool(const char *pszPoolName)
{
    UNREFERENCED_PARAMETER(pszPoolName);
}

//------------------------------------------------------------------------------
/** 
 * Allocate a new string or return an already existing string
 */
CStringPtr CStringPool::AllocateString(const char *pszString)
{
    UNREFERENCED_PARAMETER(pszString);
    CStringPtr todo;
    return todo;
}