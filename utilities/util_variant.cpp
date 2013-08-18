//
//  util_variant.cpp
//  launcher
//
//  Created by Ryan Sheffer on 2013-04-30.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "util_variant.h"

namespace Utility
{
    template<>
    const char *Variant<>::ToString(void) const
    {
        return "WRITEME";
    }
}