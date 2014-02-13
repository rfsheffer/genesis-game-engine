//
//  igraphics.h
//  graphics
//
//  Created by Ryan Sheffer on 2/5/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef IGRAPHICS_H
#define IGRAPHICS_H

#ifdef _WIN
#pragma once
#endif

#include "iExtension.h"

#define GRAPHICS_INTERFACE_NAME         "graphics"
#define GRAPHICS_INTERFACE_VERSION      1

START_EXTENSION_INTERFACE(Graphics, GRAPHICS_INTERFACE_NAME)
END_EXTENSION_INTERFACE();

#endif // IGRAPHICS_H
