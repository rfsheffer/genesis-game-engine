//
//  mathlib.h
//  math
//
//  Created by Ryan Sheffer on 2013-07-07.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//


namespace MathLib
{
    //-------------------------------------------------------------------------------
    /**
     * Purpose: Returns the SIN and COS of theta.
     */
    inline void SinCos( float radians, float *sine, float *cosine )
    {
        *sine = sin(radians);
        *cosine = cos(radians);
    }
}