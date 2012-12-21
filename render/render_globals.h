//
//  render_globals.h
//  render_gl
//
//  Created by Ryan Sheffer on 2012-10-04.
//  Copyright (c) 2012 Ryanware. All rights reserved.
//

#ifndef RENDER_GLOBALS_H
#define RENDER_GLOBALS_H

#ifdef _WIN
#pragma once
#endif

#define COLOR_BUFFER_SIZE           32
#define DEPTH_BUFFER_SIZE           8
#define ACCUM_BUFFER_SIZE           0
#define STENCIL_BUFFER_SIZE         8

// This is the lowest resolution safely supported by the game.
#define LOWEST_SCREEN_WIDTH         800
#define LOWEST_SCREEN_HEIGHT        600

#define IPHONE_SCREEEN_WIDTH        320
#define IPHONE_SCREEEN_HEIGHT       480

#define IPHONE_4_SCREEN_WIDTH       640
#define IPHONE_4_SCREEN_HEIGHT      960


// TODO: These settings should be put into a settings panel

// Sets up the window to be full screen
#define FULLSCREEN_DEFAULT          0

// Use the MAC high-res backing mode ( Adds more pixels, hence, performance loss )
#define HIGH_RES_BACKING_MODE       1

// Setting this to 1 will enable syncing to vertical retrace
#define ENABLE_VSYNC                0

// Enables the MAC specific multi-threading for OpenGL. Apples documentation
// says this feature basically threads some of the internal workings of the
// OpenGL server calls which 'could' improve performace.
#define ENABLE_MACGL_MULTI_THREAD   1

#endif // RENDER_GLOBALS_H
