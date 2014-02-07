//
//  util_floatwatch.h
//  A class for turning on float error reporting for a scope.
//
//  Created by Ryan Sheffer on 2012-10-01.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef CFLOATWATCHER
#define CFLOATWATCHER

#include <fenv.h>

namespace Utility
{
    /**
     * This is a class designed for setting up floating point
     * exception watching. Declare this class in the scope of a function
     * and when it is destroyed at the end, it will report if floating
     * point exceptions occured durring the scope of the function.
     */
    class CFloatWatcher
    {
    public:
        CFloatWatcher()
        {
            feclearexcept (FE_ALL_EXCEPT);
        }
        
        ~CFloatWatcher()
        {
            int raised = fetestexcept (FE_OVERFLOW | FE_INVALID);
            
            if (raised & FE_OVERFLOW) { /* ... */ }
            if (raised & FE_INVALID) { /* ... */ }
            
            feclearexcept (FE_ALL_EXCEPT);
        }
    };
    
}

#endif // CFLOATWATCHER
