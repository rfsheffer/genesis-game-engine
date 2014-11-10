//
//  reflectstruct.h
//  utilities
//
//  Created by Ryan Sheffer on 2014-11-09.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef utilities_reflectstruct_h
#define utilities_reflectstruct_h

//------------------------------------------------------------------------------
/** Reflect an enumerated type */
template<class T, reflect_types datatype>
class ReflectStruct : public ReflectVar<T, datatype>
{
public:
    
    /** Initialized the variable information */
    ReflectStruct(const char *pszVarName, unsigned int offset) : ReflectVar<T, datatype>(pszVarName, offset)
    {
        
    }
    
    // TODO: Variable List
};

#endif
