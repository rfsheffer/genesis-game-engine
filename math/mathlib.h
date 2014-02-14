//
//  mathlib.h
//  math
//
//  Created by Ryan Sheffer on 2013-07-07.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef math_mathlib_h
#define math_mathlib_h

namespace MathLib {}

// Math Specific
using namespace MathLib;
#include "math_constants.h"
#include "math_types.h"
#include "math_common.h"
#ifdef _32BIT
#include "math_asm.h"
#elif _64BIT
#include <xmmintrin.h>
#include "math_intrinsics.h"
#else
#error Unknown Target Machine?
#endif
#include "math_vector.h"
#include "math_angle.h"
#include "math_matrix.h"
#include "math_plane.h"
#include "math_frustum.h"

#define MATHLIB     1

#endif
