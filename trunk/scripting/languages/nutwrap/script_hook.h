//
//  testing.h
//  script_testing
//
//  Created by Ryan Sheffer on 12/22/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef SCRIPT_HOOK_H
#define SCRIPT_HOOK_H

#include "data_types.h"
#include "variant.h"

/** List of languages hooked for scripting */
enum script_language
{
    LANG_SQUIRREL_SCRIPT,
    
    NUM_SCRIPT_LANGUAGES
};

/** A callback structure containing all the argument data for the call */
struct script_call
{
    unsigned int        num_arguments;
    Utility::Variant    *arguments;
    
    unsigned int        has_return;
    Utility::Variant    returnVar;
};

/** Callback function for printing messages from a script */
typedef void (*scriptPrintFunc)(const char *pszOutString);

/** Callback function from a script */
typedef void (*scriptCallback)(script_call &callback);

//------------------------------------------------------------------------------
/** Interface for scripting language hooks */
class iScriptHook
{
public:
    /** This initializes the scripting language to be used */
    virtual bool Initialize(void) = 0;
    
    /**
     * When the script tries to print something, it will use the function
     * for output choosen by this method.
     */
    virtual void SetPrintFunction(scriptPrintFunc printFunc) = 0;
    
    /** 
     * Returns the language, defined in the script_language
     * enumerator.
     */
    virtual script_language GetLanguage(void) = 0;
    
    /** Register a function call the script can call with this method */
    virtual void RegisterCallback(const char *szCallName, scriptCallback call) = 0;
    
    /** Call a function in the script */
    virtual void CallScript(const char *szCallName, script_call call) = 0;
    
    /** Cleans up the scripting language handel */
    virtual void                        Shutdown(void) = 0;
};

iScriptHook     *GetScriptHook(script_language desiredLang);

#endif // SCRIPT_HOOK_H
