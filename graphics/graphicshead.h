//
//  enginehead.pch
//  Precompiled header for the engine
//
//  Created by Ryan Sheffer on 2013-04-19.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifdef _WIN
#pragma once
#endif

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
#include "data_mapping.h"
#include "data_pack.h"