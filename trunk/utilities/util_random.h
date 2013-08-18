//
//  util_random.h
//  Pseudo random number generation
//
//  Created by Ryan Sheffer on 2012-11-18.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef RANDOM_H
#define RANDOM_H

#ifdef _WIN32
#pragma once
#endif

#include <ctime>

namespace Utility
{
    //--------------------------------------------------------------------------
    /** A class containing a number of methods for getting random numbers. */
    class Random
    {
    public:
        //----------------------------------------------------------------------
        /**
         * Gets a random integer between min and max seeded with time
         * @param min The min value of the returned int
         * @param max The max value of the returned int
         * @return The random integer
         */
        static int         RandomIntSeeded(int min, int max)
        {
            if(max <= min)
            {
                ASSERTION(max > min, "");
                return 0;
            }
            
            // seed based on time.
            srand((unsigned)time(NULL));
            
            int range = (max - min) + 1;
            
            return (min + int(range * rand()/(RAND_MAX + 1.0)));
        }
        
        //----------------------------------------------------------------------
        /**
         * Gets a random integer between min and max
         * @param min The min value of the returned int
         * @param max The max value of the returned int
         * @return The random integer
         */
        static int         RandomInt(int min, int max)
        {
            return (((int)rand() / RAND_MAX) * (max - min));
        }
        
        //----------------------------------------------------------------------
        /**
         * Gets a random float between min and max seeded with time
         * @param min The min value of the returned int
         * @param max The max value of the returned int
         * @return The random float
         */
        static float       RandomFloat(float min, float max)
        {
            return (((float)rand() / RAND_MAX) * (max - min));
        }
    };
}

#endif