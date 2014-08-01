//
//  pywrap_error.cpp
//  pywrap
//
//  Created by Ryan Sheffer on 2014-07-05.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "scripthead.h"
#include "pywrap_error.h"

namespace pywrap {
    
    /** 
     * A list of error messages.
     * Note: There should be an error string per error.
     */
    static const char *ppszErrorMessages[] {
        "Pywrap failed to initialze",       // PYWRAP_INIT_FAIL
        "No Error",                         // PYWRAP_NO_ERROR
    };
    
    //--------------------------------------------------------------------------
    /**
     * Gets the pywrap Error string
     * @param err The error code
     */
    const char *GetPywrapError(PYWRAP_ERRORS err)
    {
#ifdef _DEBUG
        ARRAYSIZE(ppszErrorMessages);
#endif
        
        return ppszErrorMessages[err];
    }
}