//
//  scripting.cpp
//  scripting
//
//  Created by Ryan Sheffer on 2014-07-29.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "scripthead.h"
#include "scripting.h"
#include "pywrap/pywrap_main.h"


void TestTest(void)
{
    static const char * argv[] = {"arge1", "arg2"};
    pywrap_test(1, argv);
}
