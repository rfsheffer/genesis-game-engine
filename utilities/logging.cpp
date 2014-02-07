//
//  Logging.cpp
//  utilities
//
//  Created by Ryan Sheffer on 2/6/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "Logging.h"

namespace Logging
{
    void Msg(const char *pszMessage, ...)
    {
        va_list vl;
        va_start(vl, pszMessage);
        vprintf(pszMessage, vl);
    }
    
    void Warning(const char *pszMessage, ...)
    {
        va_list vl;
        va_start(vl, pszMessage);
        vprintf(pszMessage, vl);
    }
    
    void Error(const char *pszMessage, ...)
    {
        char szErrorMessage[2048];
        va_list vl;
        va_start(vl, pszMessage);
        
        vsnprintf(szErrorMessage, 2048, pszMessage, vl);
        ASSERTION(false, szErrorMessage);
        
        exit(EXIT_FAILURE);
    }
}