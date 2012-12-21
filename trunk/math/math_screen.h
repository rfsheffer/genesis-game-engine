//
//  math_screen.h
//  Math functions for working with the screen
//
//  Created by Ryan Sheffer on 2012-11-12.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef MATH_SCREEN_H
#define MATH_SCREEN_H

namespace MathLib
{
    // Calculating FOV
    float CalcFovX(float flFovY, float flAspect);
    float CalcFovY(float flFovX, float flAspect);
}

#endif // MATH_SCREEN_H
