//
//  util_random.h
//  Random Value Generation
//
//  Created by Ryan Sheffer on 10-07-10.
//  Copyright 2010 WorldScape Interactive. All rights reserved.
//

#ifndef RANDOM_H
#define RANDOM_H

#ifdef _WIN32
#pragma once
#endif

int randomint_seeded( int min, int max );
int randomint( int min, int max );
float randomfloat( float min, float max );

#endif