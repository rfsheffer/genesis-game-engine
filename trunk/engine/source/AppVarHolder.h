//
//  AppVarHolder.h
//  engine
//
//  Created by Ryan Sheffer on 2013-02-15.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef APPVAR_HOLDER_H
#define APPVAR_HOLDER_H

#ifdef _WIN
#pragma once
#endif

#include "AppVariables.h"

class AppVar
{
public:
    AppVar(const char *pszName, const char *pszVar)
    {
        pVarPointer = g_pAppVariableManager.RegisterVariable(pszName, pszVar);
    }
    
    inline bool     GetBool(void)
    {
        ASSERTION(pVarPointer, "No variable pointer in AppVar!");
        return pVarPointer->value.boolean;
    }
    
    inline float    GetFloat(void)
    {
        ASSERTION(pVarPointer, "No variable pointer in AppVar!");
        return pVarPointer->value.floating;
    }
    
    inline int      GetInteger(void)
    {
        ASSERTION(pVarPointer, "No variable pointer in AppVar!");
        return pVarPointer->value.integer;
    }
    
private:
    
    AppVariable     *pVarPointer;
};


#endif // APPVAR_HOLDER_H
