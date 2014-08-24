//
//  Reflected.h
//  scripting
//
//  Created by Ryan Sheffer on 2014-08-23.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef __scripting__Reflected__
#define __scripting__Reflected__

#include <iostream>
#include "VariableWrappers.h"

enum testenum
{
    ENUM_ELEM_1,
    ENUM_ELEM_2,
    ENUM_ELEM_3,
    ENUM_ELEM_4,
};

//------------------------------------------------------------------------------
struct ReflectedBase
{
    virtual void ReflectClass(void) = 0;
    virtual void *GetVariable(const char *pszVariableName) = 0;
};

//------------------------------------------------------------------------------
/**
 *
 */
struct ReflectedComponent
{
    int x;
    int y;
};

//------------------------------------------------------------------------------
/**
 *
 */
class BaseReflected
{
public:
    int member1;
    float member2;
    
    
    
};

//------------------------------------------------------------------------------
/**
 *
 */
class ReflectedClass : public BaseReflected
{
public:
    int member3;
    double member4;
    ReflectedComponent member5;
    
    ReflectVariable<float, DATA_FLOAT> m_testidea;
};

SCRIPTING_FUNCTION void TestReflectedClasses(void);

#endif /* defined(__scripting__Reflected__) */
