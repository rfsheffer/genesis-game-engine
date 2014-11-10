//
//  reflectclass.h
//  utilities
//
//  Created by Ryan Sheffer on 2014-11-09.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef utilities_reflectclass_h
#define utilities_reflectclass_h

// Define all reflectable types here.
// Note: It is expected that all types can be declared in a class structure.
enum reflect_types
{
    /** Plain Old Date Types, (int, float, double) */
    REFLECT_POD,
    
    /** Enumeration lists */
    REFLECT_ENUM,
    
    /** Component structures (containers, or customized structs) */
    REFLECT_STRUCT,
};

#include "reflectvar.h"
#include "reflectenum.h"
#include "reflectstruct.h"

//------------------------------------------------------------------------------
/** Reflects a class structure */
class ReflectClass
{
public:
    
    ReflectClass(const char *pszClassName)
    {
        
    }
    
    void AddReflected(ReflectVarInterface *pVar) {}
    
    void PrintMap(void){}
    
    /** The class derived from this class */
    ReflectClass            *m_pNext;
    
    /** The name of the class */
    Utility::CString        m_name;
};
#endif
