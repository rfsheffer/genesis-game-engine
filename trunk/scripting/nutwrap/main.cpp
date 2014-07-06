//
//  main.cpp
//  script_testing
//
//  Created by Ryan Sheffer on 12/4/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include <iostream>
#include <stdarg.h>
#include <stdio.h>

struct bla
{
    int a;
    int b;
};

int main(int argc, char* argv[])
{
    bla     generalBuckets[] = { { 20, 128 },   // 128bytes
                                        { 20, 64 },    // 64bytes
                                        { 20, 32 },    // 32bytes
                                        { 20, 16 } };  // 16bytes
    
    bla *test = generalBuckets;
    
    for(int i = 0; i < ARRAYSIZE(generalBuckets); ++i)
    {
        printf("%d, %d \n", test[i].a, test[i].b);
    }
    
	return 0;
}

