//
//  testing.cpp
//  script_testing
//
//  Created by Ryan Sheffer on 12/22/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "script_hook.h"

/*
 External Scripting:
 -------------------------------
 The external scripting language of choice is squirrel. It is a fast, extremely lightweight
 scripting language with a C like syntax. Even though squirrel is supported by default, it
 would be trivial to wrap LUA as it is generally like squirrel as it has a stack based
 communication API.
 
 Serialization:
 -------------------------------
 */



/** Gets a script hook handle for the requested language */
iScriptHook     *GetScriptHook(script_language desiredLang)
{
    return NULL;
}

struct functionInfo
{
	const char *pszName;
	
	int num_parameters;
	
};

enum data_type
{
	DATATYPE_INTEGER,
	DATATYPE_FLOAT,
	DATATYPE_BOOLEAN,
};
struct variant_holder
{
//    variant_holder(void *inMem, data_type inType)
//    {
//        pMem = inMem;
//        type = inType;
//    }
	void		*pMem;
	data_type	type;
};

// Optional Macros for setting up external scripts with
// hooks to variables and functions.
#define ADD_SCRIPT_VAR(member, type) \
            variant_holder _varhold_##member = { &member, type }; \
            AddScriptVariable(_varhold_##member);

#define ADD_SCRIPT_FUNC_HOOK(func) 0

class SerialAndScriptClass
{
public:
	
    /** The name of the script goes here */
	const char *GetScriptName() { return "test.nut"; }
	
    /**
     * A function to Hook to external script
     */
	int TestFunction(int wholeNum, float frac)
	{
		return int(wholeNum * frac);
	}
	
	/**
     * Added a variable hook for external scripts
     */
    void AddScriptVariable(variant_holder &var)
    {
        
    }
    
    /** Hook variables and functions for the script here */
    void InitializeScriptHooks(void)
    {
        // Adds a function callable from the external script called
        // "TestFunction" which returns an int
        //AddFunctionCall(TestFunction, "TestFunction", int, int, float);
        
        ADD_SCRIPT_VAR(testVariable,    DATATYPE_INTEGER);
        ADD_SCRIPT_VAR(testVariable2,   DATATYPE_FLOAT);
    }
    
private:
    
    int     testVariable;
	float   testVariable2;
};