//
//  reflectenum.h
//  utilities
//
//  Created by Ryan Sheffer on 2014-11-09.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef utilities_reflectenum_h
#define utilities_reflectenum_h

#include "enummap.h"

//------------------------------------------------------------------------------
/** Reflect an enumerated type */
template<class T, reflect_types datatype>
class ReflectEnum : public ReflectVar<T, datatype>
{
public:
    
    /** Initialized the variable information */
    ReflectEnum(const char *pszVarName, unsigned int offset, const EnumMapping *pEnumMap) :
    ReflectVar<T, datatype>(pszVarName, offset)
    {
        pEnumMap = pEnumMap;
    }
    
    const EnumMapping     *pEnumMap;
};

#endif
