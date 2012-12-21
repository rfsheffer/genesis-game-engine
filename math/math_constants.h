//
//  math_constants.h
//  Constant Math Values
//
//  Created by Ryan Sheffer on 15-01-11.
//  Copyright 2010 WorldScape Interactive. All rights reserved.
//

#ifndef MATH_CONSTANTS_H
#define MATH_CONSTANTS_H

#ifdef _WIN
#pragma once
#endif

namespace MathLib
{
    
// Switches for math lib
    
// Slow Operators on / off switch
//#define SLOW_VECTOR_METHODS

// All position floats are defined using this type.
typedef float vec_t;
    
// TODO: Figure out if these are even useful
#define DEG360		6.28318530717958647692528676655900576839433879875021164194988918461563281257241799725606965068
#define PI			3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534
#define DEG90		1.57079632679489661923132169163975144209858469968755291048747229615390820314310449931401741267

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

#define M_PI_F		((float)(M_PI))

#ifndef M_PI2_F
#define M_PI2_F		(float)6.28318531
#endif

#define RAD90		1.57079632679489661923
#define RAD90_F		((float)(RAD90))
#define RAD270		4.71238898038468985769
#define RAD270_F	((float)(RAD270))

#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif

#ifdef FLT_EPSILON
#undef FLT_EPSILON
#endif

#define FLT_EPSILON     1.192092896e-07F        /* smallest such that 1.0+FLT_EPSILON != 1.0 */

#define FLOAT32_NAN_BITS     (unsigned int)0x7FC00000	// not a number!
#define FLOAT32_NAN          BitsToFloat( FLOAT32_NAN_BITS )

#define VEC_T_NAN FLOAT32_NAN
    
#define PLANE_POINT_SIDE_EPSILON        0.01f
    
}

#endif // MATH_CONSTANTS_H