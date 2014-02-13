//
//  clienthead.h
//  The client precompiled header
//
//  Created by Ryan Sheffer on 2013-04-19.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "allhead.h"

// OpenGL specific
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>

namespace MathLib
{
    // Forward declaration of MathLib namespace
    // Everything should be able to access.. This might change...
}

// Math Library
#include "mathlib.h"

// Utilities
#include "util_vector.h"

// Data packaging
#include "data_mappable.h"
#include "data_pack.h"