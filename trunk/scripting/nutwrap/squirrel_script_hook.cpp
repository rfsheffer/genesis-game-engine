//
//  squirrel_script_hook.cpp
//  Wrapping a Squirrel Script around a C++ class
//
//  Created by Ryan Sheffer on 12/28/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "squirrel_script_hook.h"
#include <stdarg.h>
#include <stdio.h>

// Squirrel Script Dependencies
#include <sqstdio.h>
#include <sqstdaux.h>

#if defined(_MSC_VER) && defined(_WIN)
#pragma comment (lib ,"squirrel.lib")
#pragma comment (lib ,"sqstdlib.lib")
#endif

#ifdef SQUNICODE
#   define      scvprintf vswprintf
#else
#   define      scvprintf vsnprintf
#endif

//------------------------------------------------------------------------------
void printfunc(HSQUIRRELVM v, const SQChar *s, ...)
{
    static char szOutStr[2048];
    
	va_list vl;
	va_start(vl, s);
    scvprintf(szOutStr, 2048, s, vl);
	va_end(vl);
    
    printf("%s\n", szOutStr);
}

//------------------------------------------------------------------------------
void errorfunc(HSQUIRRELVM v, const SQChar *s, ...)
{
    static char szOutStr[2048];
    
	va_list vl;
	va_start(vl, s);
	scvprintf(szOutStr, 2048, s, vl);
	va_end(vl);
    
    printf("%s\n", szOutStr);
}

//------------------------------------------------------------------------------
/** Initializes the scripting language, and the script */
bool SquirrelScriptHook::Initialize(void)
{
    // Open Squirrel with a default stack size of 1024
    m_SquirrelVM = sq_open(1024);
    
	//REGISTRATION OF STDLIB
	//sq_pushroottable(v); //push the root table where the std function will be registered
	//sqstd_register_iolib(v);  //registers a library
	// ... call here other stdlibs string,math etc...
	//sq_pop(v,1); //pops the root table
	//END REGISTRATION OF STDLIB
	
    // registers the default error handlers
	sqstd_seterrorhandlers(m_SquirrelVM);
    
    // sets the print function
	sq_setprintfunc(m_SquirrelVM, printfunc, errorfunc);
    
    // push the root table (where the globals of the script will be stored)
	sq_pushroottable(m_SquirrelVM);
    
    // register a C callback in the root table
    //register_global_func(m_SquirrelVM, callback_foo, "callback_foo");
    
    // also prints syntax errors if any
	/*if(SQ_SUCCEEDED(sqstd_dofile(m_SquirrelVM, _SC("test.nut"), SQFalse, SQTrue)))
	{
		call_foo(m_SquirrelVM, 1, 2.5, _SC("teststring"));
	}
    else
    {
        printf("failed to load test.nut!\n");
    }*/
    
    return true;
}

//------------------------------------------------------------------------------
/**
 * Registers a callback for the squirrel script
 */
void SquirrelScriptHook::RegisterCallback(const char *szCallName, scriptCallback call)
{
    // push root table ( table root )
    /*sq_pushroottable(v);
    
    // push the name of the callback ( key )
    sq_pushstring(v, fname, -1);
    
    // create the closure ( value )
    sq_newclosure(v, f, 0);
    
    sq_newslot(v, -3, SQFalse); // new slot with key and value starting at root
    
    // pop the root table back off
    sq_pop(v, 1);
    
    return 0;*/
}

//------------------------------------------------------------------------------
/**
 * Pushes a variant argument onto the stack
 */
void PushSquirrelArgument(HSQUIRRELVM vm, Utility::Variant &var)
{
    switch(var.type)
    {
        case data::DATA_VOID:
            sq_pushuserpointer(vm, var.m_val.pData);
            break;
        case data::DATA_FLOAT:
            sq_pushfloat(vm, var.m_val.flVal);
        case data::DATA_INTEGER:
            sq_pushinteger(vm, var.m_val.iVal);
        case data::DATA_BOOLEAN:
            sq_pushbool(vm, var.m_val.bVal);
        case data::DATA_SHORT:
            sq_pushinteger(vm, (int)var.m_val.sVal);
        case data::DATA_CHARACTER:
            sq_pushstring(vm, var.m_val.pszVal, -1);
        default:
            ASSERTION(false, "Unhandled data type as squirrel parameter!");
            break;
    }
}

//------------------------------------------------------------------------------
/**
 * Puts the return value from the top of the stack into the variant
 */
void GetSquirrelReturnFromStack(HSQUIRRELVM vm, Utility::Variant &var)
{
    SQInteger retIndex = sq_gettop(vm);
    SQObjectType type = sq_gettype(vm, retIndex);
    
    switch(type)
    {
        case OT_INTEGER:
        {
            SQInteger retVal;
            sq_getinteger(vm, retIndex, &retVal);
            var.SetInt((int)retVal);
            break;
        }
        case OT_FLOAT:
        {
            SQFloat retVal;
            sq_getfloat(vm, retIndex, &retVal);
            var.SetFloat(retVal);
        }
        case OT_BOOL:
        {
            SQBool retVal;
            sq_getbool(vm, retIndex, &retVal);
            var.SetBool(retVal);
        }
        case OT_STRING:
        {
            const SQChar *retVal;
            sq_getstring(vm, retIndex, &retVal);
            // TODO: Need to copy this into a string pool or something.
            ASSERTION(false, "Implement string returns!");
        }
        default:
            ASSERTION(false, "Unhandled data type as squirrel function return!");
            break;
    }
}

//------------------------------------------------------------------------------
/**
 * Calls a function within the squirrel script
 */
void SquirrelScriptHook::CallScript(const char *szCallName, script_call call)
{
    // saves the stack size before the call
	SQInteger top = sq_gettop(m_SquirrelVM);
    
    // pushes the global table
	sq_pushroottable(m_SquirrelVM);
    
	sq_pushstring(m_SquirrelVM, _SC(szCallName), -1);
    
    // gets the field 'szCallName' from the global table
	if(SQ_SUCCEEDED(sq_get(m_SquirrelVM, -2)))
    {
        // push the 'this' (in this case is the global table)
		sq_pushroottable(m_SquirrelVM);
        
        // push arguments onto the stack
        for(int i = 0; i < call.num_arguments; ++i)
        {
            PushSquirrelArgument(m_SquirrelVM, call.arguments[i]);
        }
        
        // call the function
		sq_call(m_SquirrelVM,
                call.num_arguments + 1,
                (call.has_return != 0)?SQTrue:SQFalse,
                SQTrue);
	}
    
    if(call.has_return)
    {
        GetSquirrelReturnFromStack(m_SquirrelVM, call.returnVar);
    }
    
    // restores the original stack size
	sq_settop(m_SquirrelVM, top);
}

//------------------------------------------------------------------------------
/** 
 * Closes the Squirrel Script Handle
 */
void SquirrelScriptHook::Shutdown(void)
{
    sq_pop(m_SquirrelVM, 1); //pops the root table
	sq_close(m_SquirrelVM);
}

//------------------------------------------------------------------------------
// squirrel will call this
/*SQInteger callback_foo(HSQUIRRELVM v)
{
    SQInteger nargs = sq_gettop(v); //number of arguments
    if(nargs != 2)
    {
        return sq_throwerror(v, "not enough parameters"); //throws an exception
    }
    
    if(sq_gettype(v, 2) != OT_INTEGER)
    {
        return sq_throwerror(v, "invalid param");
    }
    
    SQInteger retVal;
    sq_getinteger(v, 2, &retVal);
    
    // push the return value
    sq_pushinteger(v, retVal);
    return 1;
}*/