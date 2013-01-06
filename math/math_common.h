//
//  common_math.h
//  Common Math Functions
//
//  Created by Ryan Sheffer on 10-07-10.
//  Copyright 2010 Ryan Sheffer. All rights reserved.
//

#ifndef MATH_COMMON_H
#define MATH_COMMON_H

#ifdef _WIN
#pragma once
#endif

namespace MathLib
{

#ifndef MIN
#define MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#endif
    
#ifndef MAX
#define MAX( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#endif
    
#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif
    
#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif
    
    // Returns the fraction of completion of an interval
    // (0.0 == start, 1.0 == finish)
    float GetIntervalFrac(float intervalEnd, float intervalLength, float time);
    
    // A union for getting an integer version of a float
    // and for doing quick checks for negative.
    union Float_t
    {
        float   f;
        int     i;
        
        Float_t(float num = 0.0f) :f(num){}
        bool Negative() const { return i < 0; }
    };
    
    // ====================================================
    // Bruce Dawsons floating point comparison functions
    // ====================================================
    // If two floats are adjacent, we say that they differ
    // by one Unit in the last Place (ULP)
    
    // For dealing with numbers not near zero
    // Uses Relative check
    bool AlmostEqualRelative(float A, float B, float maxRelDiff = FLT_EPSILON);
    
    // For dealing with numbers not near Zero
    // Uses ULP check
    bool AlmostEqualUlps(float A, float B, int maxUlpsDiff = 1);
    
    // For dealing with numbers near Zero
    // Uses Relative check
    bool AlmostEqualRelativeAndAbs(float A, float B, float maxDiff, float maxRelDiff = FLT_EPSILON);
    
    // For dealing with numbers near Zero
    // Uses ULP check
    bool AlmostEqualUlpsAndAbs(float A, float B, float maxDiff, int maxUlpsDiff = 1);
    
#define COMPILE_TIME_ASSERT_BASETYPES( pred ) {typedef char compile_time_assert_type[(pred) ? 1 : -1];}
    
    FORCEINLINE unsigned int FloatBits( const vec_t &f )
    {
        union Convertor_t
        {
            vec_t f;
            unsigned int ul;
        }tmp;
        
        COMPILE_TIME_ASSERT_BASETYPES( sizeof( tmp ) == 4 && sizeof( tmp.f ) == 4 && sizeof( tmp.ul ) == 4 );
        tmp.f = f;
        return tmp.ul;
    }
    
    FORCEINLINE vec_t BitsToFloat( unsigned int i )
    {
        union Convertor_t
        {
            vec_t f;
            unsigned int ul;
        }tmp;
        
        COMPILE_TIME_ASSERT_BASETYPES( sizeof( tmp ) == 4 && sizeof( tmp.f ) == 4 && sizeof( tmp.ul ) == 4 );
        tmp.ul = i;
        return tmp.f;
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Checks if this float is valid
    //-----------------------------------------------------------------------------
    FORCEINLINE bool IsFinite( vec_t f )
    {
#ifdef CHEAP_ISINFINITE
        return f = f && fabs(f) <= FLT_MAX;
#else
        return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
#endif
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Flips a floats sign bit to positive.
    //-----------------------------------------------------------------------------
    inline float FloatMakePositive( vec_t f )
    {
        return fabsf( f );
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Flips a floats sign bit to negative.
    //-----------------------------------------------------------------------------
    inline float FloatNegate( vec_t f )
    {
        return -f;
    }
    
    inline float FloatMakeNegative( vec_t f )
    {
        return -fabsf( f );
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Returns the first power of 2 greater than 'a'.
    //-----------------------------------------------------------------------------
    inline int next_p2( int a )
    {
        int rval = 2;
        // Shift 1 bit over to get all powers of 2 until the power is greater than a.
        while( rval < a ) rval <<= 1;
        return rval;
    }
    
    float AngleNormalize( float angle );
    
    float AngleDiff( float destAngle, float srcAngle );
    
    float AngleNormalizePositive( float angle );
    
    bool AnglesAreEqual( float a, float b, float tolerance );
}


#endif // MATH_COMMON_H