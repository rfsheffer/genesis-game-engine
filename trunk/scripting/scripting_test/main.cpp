//
//  main.cpp
//  scripting_test
//
//  Created by Ryan Sheffer on 2014-07-31.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "../scripthead.h"
#include "../tests/Reflected.h"
#include "ideas.h"


int main(int argc, const char * argv[])
{
    // Different offsets thanks to an 8 byte virtual table pointer
    //printf("%lu and %lu\n", offsetof(PodBase, x), offsetof(NonPodDerived, x));
    
    TestReflectedClasses();
    
    return 0;
}

