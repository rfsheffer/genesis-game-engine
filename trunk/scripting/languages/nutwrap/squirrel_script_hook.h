//
//  squirrel_script_hook.h
//  Wrapping a Squirrel Script around a C++ class
//
//  Created by Ryan Sheffer on 12/28/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef SQUIRREL_SCRIPT_HOOK_H
#define SQUIRREL_SCRIPT_HOOK_H

#include "script_hook.h"
#include <squirrel.h>

//------------------------------------------------------------------------------
/** Squirrel Script hook */
class SquirrelScriptHook : public iScriptHook
{
public:
    
    bool        Initialize(void);
    
    /** Returns which scripting language, which is Squirrel in this case */
    script_language    GetLanguage(void){return LANG_SQUIRREL_SCRIPT;}
    
    void        RegisterCallback(const char *szCallName, scriptCallback call);
    void        CallScript(const char *szCallName, script_call call);
    
    void        Shutdown(void);
    
private:
    
    /** Virtual machine handel for Squirrel Script */
    HSQUIRRELVM     m_SquirrelVM;
};

#endif // SQUIRREL_SCRIPT_HOOK_H
