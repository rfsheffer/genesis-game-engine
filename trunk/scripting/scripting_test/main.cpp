//
//  main.cpp
//  scripting_test
//
//  Created by Ryan Sheffer on 2014-07-31.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include <iostream>
#include <string>

using std::string;

struct Name { int hash; string text; };
struct Primitive { Name name; };
struct Type : Primitive { int size; };
struct EnumConstant : Primitive { int value; };
struct Enum : Type { EnumConstant *constants; };
struct Field : Primitive { Type type; int offset; };
struct Function : Primitive { Field return_parameter; Field *parameters; };
struct Class : Type { Field *fields; Function *functions; };
struct Namespace : Primitive { Enum *enums; Class *classes; Function *functions; };

struct PodBase
{
    int x;
};
struct NonPodDerived : public PodBase
{
    virtual void f(){}
};


int main(int argc, const char * argv[])
{
    // Different offsets thanks to an 8 byte virtual table pointer
    printf("%lu and %lu\n", offsetof(PodBase, x), offsetof(NonPodDerived, x));
    
    return 0;
}

