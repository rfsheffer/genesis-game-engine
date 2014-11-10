//
//  Reflected.h
//  scripting
//
//  Created by Ryan Sheffer on 2014-08-23.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef __scripting__Reflected__
#define __scripting__Reflected__


#include "reflection/reflectionmap.h"

enum testenum
{
    ENUM_ELEM_1,
    ENUM_ELEM_2,
    ENUM_ELEM_3,
    ENUM_ELEM_4,
};

//------------------------------------------------------------------------------
/**
 *
 */
struct ReflectedComponent : public CReflected
{
    int x;
    int y;
    
    ReflectClass *Init(ReflectClass *pNextClass)
    {
        return NULL;
    }
};

//------------------------------------------------------------------------------
/**
 *
 */
class BaseReflected : public CReflected
{
public:
    testenum myEnum;
    
    virtual ReflectClass *Init(ReflectClass *pNextClass);
};

//------------------------------------------------------------------------------
/**
 *
 */
class ReflectedClass : public BaseReflected
{
public:
    int member3;
    ReflectedComponent member5;
    
    ReflectClass *Init(ReflectClass *pNextClass);
};

SCRIPTING_FUNCTION void TestReflectedClasses(void);

#endif /* defined(__scripting__Reflected__) */
