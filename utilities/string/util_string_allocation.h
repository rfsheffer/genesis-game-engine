//
//  string_pointer.h
//  String pointer, for holding a pointer to a string in a string pool.
//
//  Created by Ryan Sheffer on 12/28/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef STRING_POINTER_H
#define STRING_POINTER_H

#ifdef _WIN
#pragma once
#endif

namespace Utility
{
//------------------------------------------------------------------------------
/**
 * The string class contains a pointer to an imutable string of characters. The
 * string was allocated by an allocator, so the CString class is just a holder
 * for a pointer, created by the allocator. This can be very useful for string
 * comparisons, as if all strings are allocated and assigned to CStrings, just
 * the pointer addresses will be compared, and not the whole series of characters.
 */
class CString
{
public:
    CString() : m_pszPoolString(NULL) {}
    CString(const char *pszAllocedStr) : m_pszPoolString(pszAllocedStr) {}
    
    FORCEINLINE bool operator==(const CString& str) const
    {
        return str.m_pszPoolString == m_pszPoolString;
    }
    
    const char *m_pszPoolString;
};

// A blank C string for comparing against null.
#define NULL_STRING     CString()
    
} // namespace Utility

#endif // STRING_POINTER_H
