//
//  reflectclass.h
//  utilities
//
//  Created by Ryan Sheffer on 2014-11-09.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef utilities_reflectmap_h
#define utilities_reflectmap_h

// Required Utilities
#include "string/util_string_pool.h"

// Class, the highest structure
#include "reflectclass.h"

//------------------------------------------------------------------------------
/** Base of any reflected structure */
class CReflected
{
public:
    virtual ReflectClass *Init(ReflectClass *pNextClass) = 0;
};

#endif
