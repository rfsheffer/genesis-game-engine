//
//  util_random.cpp
//  Random Value Generation
//
//  Created by Ryan Sheffer on 10-07-10.
//  Copyright 2010 WorldScape Interactive. All rights reserved.
//

#include "stdafx.h"
#include <ctime>

int randomint_seeded( int min, int max ) 
{ 
	if ( max <= min )
	{
		assert( true );
		return 0;
	}

	// seed based on time.
	srand( (unsigned)time( NULL ) );

	int range = ( max-min ) + 1;

	return (min + int(range * rand()/( RAND_MAX + 1.0 )));
}

int randomint( int min, int max )
{
	return (((int)rand() / RAND_MAX) * ( max - min ));
}

float randomfloat( float min, float max )
{
	return (((float)rand() / RAND_MAX) * ( max - min ));
}