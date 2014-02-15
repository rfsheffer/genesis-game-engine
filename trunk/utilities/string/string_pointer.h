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

class CStringPtr
{
public:
    CStringPtr() : pszPtr(NULL) {}
    
    FORCEINLINE bool operator==(const CStringPtr& str) const
    {
        return str.pszPtr == pszPtr;
    }
    
    const char *pszPtr;
};

#endif // STRING_POINTER_H
