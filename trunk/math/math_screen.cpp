//
//  math_screen.cpp
//  Math functions for working with the screen
//
//  Created by Ryan Sheffer on 2012-11-12.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "mathhead.h"
#include "math_screen.h"

namespace MathLib
{
    //-----------------------------------------------------------------------------
    // Purpose: Calculate the X FOV if you have the Y FOV and the aspect ration of the screen
    //-----------------------------------------------------------------------------
    float CalcFovX(float flFovY, float flAspect)
    {
        return RAD2DEG(atan(tan(DEG2RAD(flFovY) * 0.5f) / flAspect)) * 2.0f;
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Calculate the Y FOV if you have the X FOV and the aspect ration of the screen
    //-----------------------------------------------------------------------------
    float CalcFovY(float flFovX, float flAspect)
    {
        // Check constraints. Anything over 180
        if(flFovX < 1 || flFovX > 180)
        {
            ASSERTION(false, "FOV X is out of range in CalcFovY");
            flFovX = 90.0f; // Default FOV of 90
        }
        
        return RAD2DEG(atan(tan(DEG2RAD(flFovX) * 0.5f) / flAspect)) * 2.0f;
    }
}
