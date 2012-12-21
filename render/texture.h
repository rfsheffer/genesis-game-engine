//
//	texture.h
//  Texture File Handling
//
//  Created by Ryan Sheffer on 10-07-10.
//  Copyright 2010 WorldScape Interactive. All rights reserved.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef _WIN32
#pragma once
#endif

struct texture_t
{
	//char	name[MAX_TEX_NAME_LEN];         // Don't think this is needed..
	unsigned int	width;					// Image Width
	unsigned int	height;					// Image Height
    unsigned int	bpp;					// Image Color Depth In Bits Per Pixels
	unsigned int	texID;					// Texture ID Used To Select A Texture
};

#endif // TEXTURE_H