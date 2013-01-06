//
//  base_types.h
//  Static Math Values
//
//  Created by Ryan Sheffer on 10-07-10.
//  Copyright 2010 Ryan Sheffer. All rights reserved.
//

#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#ifdef _WIN
#pragma once
#endif

namespace MathLib
{
    // Add types specific to math here.
    enum side_t
    {
        SIDE_FRONT,
        SIDE_BACK,
        SIDE_ON
    };
}

#endif // MATH_TYPES_H