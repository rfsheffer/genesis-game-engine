//
//  AppVariables.cpp
//  Application Wide Variables
//
//  Created by Ryan Sheffer on 2013-02-15.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "enginehead.h"
#include "AppVariables.h"
#include "ascii_table.h"

/** Global application variable manager */
AppVariableManager  g_pAppVariableManager;

/**
 * Constructor for application variable
 */
AppVariable::AppVariable(const char *pszVarName, const char *pszVar)
{
    util_strncpy(szName, pszVarName, MAX_APPVAR_NAME_SIZE);
    
    // Determine what the variable is
    size_t varLen = strlen(pszVar);
    if(varLen == 1 && (pszVar[0] == ASCII_ZERO || pszVar[0] == ASCII_ONE))
    {
        type = VAR_TYPE_BOOLEAN;
        value.boolean = (pszVar[0] == ASCII_ZERO)?false:true;
    }
    else
    {
        type = VAR_TYPE_INTEGER;
        
        for(int i = 0; i < varLen; ++i)
        {
            if(pszVar[i] == ASCII_PERIOD)
            {
                type = VAR_TYPE_FLOATING;
                break;
            }
        }
        
        if(type == VAR_TYPE_INTEGER)
        {
            value.integer = atoi(pszVar);
        }
        else
        {
            double toDouble = atof(pszVar);
            ASSERT_VALID_DOUBLE_TO_FLOAT(toDouble);
            value.floating = (float)toDouble;
        }
    }
}

/**
 * Register a variable with the application variable manager
 */
AppVariable *AppVariableManager::RegisterVariable(const char *pszVarName,
                                                  const char *pszVar)
{
    for(unsigned int i = 0; i < m_varStore.Count(); ++i)
    {
        if(strncmp(m_varStore[i].szName, pszVarName, MAX_APPVAR_NAME_SIZE) == 0)
        {
            return &m_varStore[i];
        }
    }
    
    unsigned int index = m_varStore.AddElementToBack(AppVariable(pszVarName, pszVar));
    return &m_varStore.Element(index);
}