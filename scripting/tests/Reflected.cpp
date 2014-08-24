//
//  Reflected.cpp
//  scripting
//
//  Created by Ryan Sheffer on 2014-08-23.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "scripthead.h"
#include "Reflected.h"

//------------------------------------------------------------------------------
/**
 * Tests the reflected classes
 */
void TestReflectedClasses(void)
{
    ReflectedClass *pClassTest = new ReflectedClass();
    
    delete pClassTest;
}