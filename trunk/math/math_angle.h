//
//  math_angle.h
//  Angle Classes
//
//  Created by Ryan Sheffer on 2012-11-10.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef MATH_Angle_H
#define MATH_Angle_H

#ifdef _WIN32
#pragma once
#endif

namespace MathLib
{
    
    enum angle_rots
    {
        PITCH,
        YAW,
        ROLL
    };
    
    //-----------------------------------------------------------------------------
    // Radian Euler Angle Class
    //-----------------------------------------------------------------------------
    class Angle
    {
    public:
        vec_t	x, y, z;
        
        Angle(){}
        Angle(vec_t inX, vec_t inY, vec_t inZ)
        {
            Init(inX, inY, inZ);
        }
        
        inline void Init(vec_t inX = 0, vec_t inY = 0, vec_t inZ = 0)
        {
            x = inX;
            y = inY;
            z = inZ;
        }
        
        inline void Zero(void)
        {
            Init();
        }
        
        // Array Access
        vec_t operator[](angle_rots i) const
        {
#ifdef _DEBUG
            ASSERTION(i >= PITCH && i <= ROLL, "Angle: operator[] operand out of range!");
#endif
            switch(i)
            {
                case PITCH:
                    return x;
                case YAW:
                    return y;
                case ROLL:
                    return z;
            }
            
            return -1;
        }
        
        vec_t& operator[](angle_rots i)
        {
#ifdef _DEBUG
            ASSERTION(i >= PITCH && i <= ROLL, "Angle: operator[] operand out of range!");
#endif
            switch(i)
            {
                case PITCH:
                    return x;
                case YAW:
                    return y;
                case ROLL:
                    return z;
            }
            
            return z;
        }
        
        // Getters
        inline float GetPitchDegrees(void) const;
        inline float GetYawDegrees(void) const;
        inline float GetRollDegrees(void) const;
        
        // Equality
        inline bool operator==(const Angle &inAngle) const;
        inline bool operator!=(const Angle &inAngle) const;
        
        // Arithmetic Operations
        inline Angle&	operator+=(const Angle &inAngle);
        inline Angle&	operator-=(const Angle &inAngle);
        inline Angle&	operator*=(float multiplicand);
        inline Angle&	operator/=(float dividend);
        
        inline Angle&	operator*=(const Angle &inAngle);
        inline Angle&	operator/=(const Angle &inAngle);
    };
    
    //-----------------------------------------------------------------------------
    // Purpose: Angle Element getters in degrees
    //-----------------------------------------------------------------------------
    inline float Angle::GetPitchDegrees(void) const
    {
        return RAD2DEG(x);
    }
    inline float Angle::GetYawDegrees(void) const
    {
        return RAD2DEG(y);
    }
    inline float Angle::GetRollDegrees(void) const
    {
        return RAD2DEG(z);
    }
    
    //-----------------------------------------------------------------------------
    // Operator Overloads
    //-----------------------------------------------------------------------------
    inline bool Angle::operator==(const Angle& inAngle) const
    {
        return (inAngle.x == x) && (inAngle.y == y) && (inAngle.z == z);
    }
    inline bool Angle::operator!=(const Angle& inAngle) const
    {
        return (inAngle.x != x) || (inAngle.y != y) || (inAngle.z != z);
    }
    
    // arithmetic operations
    inline Angle&	Angle::operator+=(const Angle &inAngle)
    {
        x += inAngle.x;
        y += inAngle.y;
        z += inAngle.z;
        
        return *this;
    }
    inline Angle&	Angle::operator-=(const Angle &inAngle)
    {
        x -= inAngle.x;
        y -= inAngle.y;
        z -= inAngle.z;
        
        return *this;
    }
    inline Angle&	Angle::operator*=(float multiplicand)
    {
        x *= multiplicand;
        y *= multiplicand;
        z *= multiplicand;
        
        return *this;
    }
    inline Angle&	Angle::operator/=(float dividend)
    {
        ASSERTION(dividend != 0, "Angle: Dividing by zero!");
        
        x /= dividend;
        y /= dividend;
        z /= dividend;
        
        return *this;
    }
    
    inline Angle&	Angle::operator*=(const Angle &inAngle)
    {
        x *= inAngle.x;
        y *= inAngle.y;
        z *= inAngle.z;
        
        return *this;
    }
    
    inline Angle&	Angle::operator/=(const Angle &inAngle)
    {
        ASSERTION(inAngle.x != 0 && inAngle.y != 0 && inAngle.z != 0, "Angle: Dividing by zero!");
        
        x /= inAngle.x;
        y /= inAngle.y;
        z /= inAngle.z;
        
        return *this;
    }
    
    //-----------------------------------------------------------------------------
    // Angle Functions
    //-----------------------------------------------------------------------------
    void AngleVectors(const Angle &ang, Vector3& left, Vector3& up, Vector3& forward);
    
} // namespace mathLib

#endif // MATH_Angle_H