//
//  common_math.cpp
//
//  Created by Ryan Sheffer on 2012-10-08.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

//#include "allhead.pch"

namespace MathLib
{
    // Returns the fraction of completion of an interval
    // (0.0 == start, 1.0 == finish)
    float GetIntervalFrac(float intervalEnd, float intervalLength, float time)
    {
        float timeToIntervalEnd = intervalEnd - time;
        float t = (intervalLength - timeToIntervalEnd) / intervalLength;
        
        return t;
    }
    
    // For dealing with numbers not near zero
    // Uses Relative check
    bool AlmostEqualRelative(float A, float B, float maxRelDiff)
    {
        // Calculate the difference
        float diff = fabs(A - B);
        A = fabs(A);
        B = fabs(B);
        // Find the largest
        float largest = (B > A) ? B : A;
        
        if(diff <= largest * maxRelDiff)
            return true;
        
        return false;
    }
    
    // For dealing with numbers not near Zero
    // Uses ULP check
    bool AlmostEqualUlps(float A, float B, int maxUlpsDiff)
    {
        Float_t uA(A);
        Float_t uB(B);
        
        // Different signs means they do not match.
        if(uA.Negative() != uB.Negative())
        {
            // Check for equality to make sure +0==-0
            if(A == B)
                return true;
            return false;
        }
        
        // Find the difference in ULPs.
        int ulpsDiff = abs(uA.i - uB.i);
        if(ulpsDiff <= maxUlpsDiff)
            return true;
        
        return false;
    }
    
    // For dealing with numbers near Zero
    // Uses Relative check
    bool AlmostEqualRelativeAndAbs(float A, float B, float maxDiff, float maxRelDiff)
    {
        // Check if the numbers are really close -- needed
        // when comparing numbers near zero
        float diff = fabs(A - B);
        if (diff <= maxDiff)
            return true;
        
        A = fabs(A);
        B = fabs(B);
        float largest = (B > A) ? B : A;
        
        if (diff <= largest * maxRelDiff)
            return true;
        
        return false;
    }
    
    // For dealing with numbers near Zero
    // Uses ULP check
    bool AlmostEqualUlpsAndAbs(float A, float B, float maxDiff, int maxUlpsDiff)
    {
        // Check if the numbers are really close -- needed
        // when comparing numbers near zero.
        float absDiff = fabs(A - B);
        if (absDiff <= maxDiff)
            return true;
        
        Float_t uA(A);
        Float_t uB(B);
        
        // Different signs means they do not match.
        if (uA.Negative() != uB.Negative())
            return false;
        
        // Find the difference in ULPs.
        int ulpsDiff = abs(uA.i - uB.i);
        if (ulpsDiff <= maxUlpsDiff)
            return true;
        
        return false;
    }
    
    float AngleNormalize( float angle )
    {
        angle = fmodf(angle, 360.0f);
        if (angle > 180)
        {
            angle -= 360;
        }
        if (angle < -180)
        {
            angle += 360;
        }
        return angle;
    }
    
    float AngleDiff( float destAngle, float srcAngle )
    {
        float delta;
        
        delta = fmodf(destAngle - srcAngle, 360.0f);
        if ( destAngle > srcAngle )
        {
            if ( delta >= 180 )
                delta -= 360;
        }
        else
        {
            if ( delta <= -180 )
                delta += 360;
        }
        return delta;
    }
    
    float AngleNormalizePositive( float angle )
    {
        angle = fmodf( angle, 360.0f );
        
        if (angle < 0.0f)
        {
            angle += 360.0f;
        }
        
        return angle;
    }
    
    bool AnglesAreEqual( float a, float b, float tolerance )
    {
        return (fabs( AngleDiff( a, b ) ) < tolerance);
    }
}