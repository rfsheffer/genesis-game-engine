//
//  Logging.h
//  Methods for logging information about execution.
//
//  Created by Ryan Sheffer on 2/6/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef LOGGING_H
#define LOGGING_H

#ifdef _WIN
#pragma once
#endif

namespace Logging
{
    /** Logs a basic message */
    UTILITIES_FUNCTION
    void Msg(const char *pszMessage, ...);
    
    /** Logs a warning message */
    UTILITIES_FUNCTION
    void Warning(const char *pszMessage, ...);
    
    /** Logs an error message, and exits */
    UTILITIES_FUNCTION
    void Error(const char *pszMessage, ...);
}

#endif // LOGGING_H
