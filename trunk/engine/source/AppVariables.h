//
//  AppVariables.h
//  Application Wide Variables
//
//  Created by Ryan Sheffer on 2013-02-15.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef APPVARIABLES_H
#define APPVARIABLES_H

#ifdef _WIN
#pragma once
#endif

#define MAX_APPVAR_NAME_SIZE        64

/**
 * An application variable
 */
struct AppVariable
{
    AppVariable(const char *pszVarName, const char *pszVar);
    
    char    szName[MAX_APPVAR_NAME_SIZE];
    
    union
    {
        int     integer;
        float   floating;
        bool    boolean;
    } value;
    
    enum var_type
    {
        VAR_TYPE_INTEGER,
        VAR_TYPE_FLOATING,
        VAR_TYPE_BOOLEAN
    };
    
    /** The type of variable stored in value */
    var_type     type;
};

/**
 * Application Variable Manager
 */
class AppVariableManager
{
public:
    
    AppVariable     *RegisterVariable(const char *pszVarName, const char *pszVar);
    
    // TODO: Use a better container class.
    Utility::Vector<AppVariable>    m_varStore;
};

extern AppVariableManager g_pAppVariableManager;


#endif // APPVARIABLES_H
