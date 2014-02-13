//
//  allhead.pch
//  This is the master precompiled header used by all genesis extensions and
//  Libraries. It should only contain the bare minimum for running a genesis app.
//
//  Created by Ryan Sheffer on 2013-04-19.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifdef _WIN
#pragma once
#endif

// Standard C Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#if defined(_WIN)
#include <malloc.h>
#endif
#include <memory.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <stdint.h>

// C++ Libraries
#include <new> // For new override
#include <vector> // TODO: Get rid of me!
#include <map> // TODO: Get rid of me!

#if defined(_MAC) || defined(_LINUX)

// Unix Dynamic Linker
#include <dlfcn.h>

#elif defined(_WIN)

#ifdef INCLUDE_WINDOWS_HEADER
#include "targetver.h"

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#endif // INCLUDE_WINDOWS_HEADER

#include <tchar.h>

#endif // platform specific

// Platform macros and defines
#include "types.h"
#include "macros.h"
#include "foundation_constants.h"

// Utilities ( Always included in projects )
#include "../utilities/utilities.h"
#include "../utilities/gstdlib/gstdlib.h"
#include "../platform/platform_constants.h"
#include "../platform/IPlatform.h"
#include "../utilities/interfaces/interfaces.h"
#include "../utilities/logging.h"

// Debug specific stuff like ASSERTION
#include "../utilities/common/debug.h"