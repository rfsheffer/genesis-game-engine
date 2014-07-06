//
//  pywrap_error.h
//  pywrap
//
//  Created by Ryan Sheffer on 2014-07-05.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef PYWRAP_ERROR_H
#define PYWRAP_ERROR_H

namespace pywrap {
    
    /**
     * Pywrap Errors.
     * Note: If you add a new error, add a new string in the cpp file.
     */
    enum PYWRAP_ERRORS
    {
        PYWRAP_INIT_FAIL,
        
        PYWRAP_NO_ERROR,
    };
    
    const char *GetPywrapError(PYWRAP_ERRORS err);
}


#endif // PYWRAP_ERROR_H
