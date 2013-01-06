//
//  math_vector.h
//  Vector Classes
//
//  Created by Ryan Sheffer on 2012-11-10.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#ifdef _WIN32
#pragma once
#endif

namespace MathLib
{
    
#ifdef _CHECK_VECTOR_FLOATS
#define CHECK_VALID( _v)	ASSERTION( (_v).IsValid(), "Invalid Vector!" )
#else
#define CHECK_VALID( _v)
#endif
    
    //=========================================================
    // 3D Vector3
    //=========================================================
    class Vector3
    {
    public:
        // Members
        vec_t x, y, z;
        
        // Construction/destruction:
        Vector3(void)
        {
#ifdef _DEBUG
            // Initialize to NAN to catch errors
            x = y = z = VEC_T_NAN;
#endif
        }
        
        Vector3(vec_t X, vec_t Y, vec_t Z)
        {
            x = X; y = Y; z = Z;
            CHECK_VALID(*this);
        }
        
        // Initialization
        void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f)
        {
            x = ix;
            y = iy;
            z = iz;
        }
        
        // array access...
        vec_t operator[](int i) const;
        vec_t& operator[](int i);
        
        // Got any nasty NAN's?
        inline bool IsValid() const;
        inline void Invalidate();
        
        // Initialization methods
        void Random( vec_t minVal, vec_t maxVal );
        inline void Zero(); ///< zero out a vector
        
        // equality
        FORCEINLINE bool operator==(const Vector3& v) const;
        FORCEINLINE bool operator!=(const Vector3& v) const;
        
        // arithmetic operations
        FORCEINLINE Vector3&	operator+=(const Vector3 &v);
        FORCEINLINE Vector3&	operator-=(const Vector3 &v);
        FORCEINLINE Vector3&	operator*=(const Vector3 &v);
        FORCEINLINE Vector3&	operator*=(float s);
        FORCEINLINE Vector3&	operator/=(const Vector3 &v);
        FORCEINLINE Vector3&	operator/=(float s);
        FORCEINLINE Vector3&	operator+=(float fl);
        FORCEINLINE Vector3&	operator-=(float fl);
        
#ifdef SLOW_VECTOR_METHODS
        // arithmetic operations
        Vector3	operator-(void) const;
        
        Vector3	operator+(const Vector3& v) const;
        Vector3	operator-(const Vector3& v) const;
        Vector3	operator*(const Vector3& v) const;
        Vector3	operator/(const Vector3& v) const;
        Vector3	operator*(float fl) const;
        Vector3	operator/(float fl) const;
 #endif       
        // assignment
        Vector3& operator=(const Vector3 &vOther);

        
        // negate the vector components
        void	Negate();
        
        // Get the vector's magnitude.
        inline vec_t	Length() const;
        
        // Get the vector's magnitude squared.
        FORCEINLINE vec_t LengthSqr(void) const
        {
            CHECK_VALID(*this);
            return (x*x + y*y + z*z);
        }
        
        // return true if this vector is (0,0,0) within tolerance
        bool IsZero( float tolerance = 0.01f ) const
        {
            return (x > -tolerance && x < tolerance &&
                    y > -tolerance && y < tolerance &&
                    z > -tolerance && z < tolerance);
        }
        
        vec_t	NormalizeInPlace();
        bool	IsLengthGreaterThan( float val ) const;
        bool	IsLengthLessThan( float val ) const;
        
        // Get the distance from this vector to the other one.
        vec_t	DistTo(const Vector3 &vOther) const;
        
        // Get the distance from this vector to the other one squared.
        FORCEINLINE vec_t DistToSqr(const Vector3 &vOther) const
        {
            Vector3 delta;
            
            delta.x = x - vOther.x;
            delta.y = y - vOther.y;
            delta.z = z - vOther.z;
            
            return delta.LengthSqr();
        }
        
        // Cross product of two vectors to this vector.
        void CrossProduct( const Vector3 &v1, const Vector3 &v2 )
        {
            x = (v1.y * v2.z) - (v1.z * v2.y);
            y = (v1.z * v2.x) - (v1.x * v2.z);
            z = (v1.x * v2.y) - (v1.y * v2.x);
        }
        
        // Multiply, add, and assign to this (ie: *this = a + b * scalar). This
        // is about 12% faster than the actual vector equation (because it's done per-component
        // rather than per-vector).
        void	MulAdd(const Vector3& a, const Vector3& b, float scalar);
        
        
        // 2d
        vec_t	Length2D(void) const;
        vec_t	Length2DSqr(void) const;
    };
    
    //-----------------------------------------------------------------------------
    // Array access
    //-----------------------------------------------------------------------------
    inline vec_t& Vector3::operator[](int i)
    {
        ASSERTION( (i >= 0) && (i < 3), "Vector3: Out of range []" );
        return ((vec_t*)this)[i];
    }
    
    inline vec_t Vector3::operator[](int i) const
    {
        ASSERTION( (i >= 0) && (i < 3), "Vector3: Out of range []" );
        return ((vec_t*)this)[i];
    }
    
    //-----------------------------------------------------------------------------
    // Dot Product
    //-----------------------------------------------------------------------------
    inline float DotProduct(const Vector3& a, const Vector3& b)
    {
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Gets the cross product of two vectors
    //-----------------------------------------------------------------------------
    inline void CrossProduct(const Vector3 &v1, const Vector3 &v2, Vector3 &out)
    {
        out.x = (v1.y * v2.z) - (v1.z * v2.y);
        out.y = (v1.z * v2.x) - (v1.x * v2.z);
        out.z = (v1.x * v2.y) - (v1.y * v2.x);
    }
    
    //-----------------------------------------------------------------------------
    // Common vector inlines.
    //-----------------------------------------------------------------------------
    FORCEINLINE void Vector3Add( const Vector3& a, const Vector3& b, Vector3& c )
    {
        CHECK_VALID(a);
        CHECK_VALID(b);
        c.x = a.x + b.x;
        c.y = a.y + b.y;
        c.z = a.z + b.z;
    }
    
    FORCEINLINE void Vector3Subtract( const Vector3& a, const Vector3& b, Vector3& c )
    {
        CHECK_VALID(a);
        CHECK_VALID(b);
        c.x = a.x - b.x;
        c.y = a.y - b.y;
        c.z = a.z - b.z;
    }
    
    FORCEINLINE void Vector3Multiply( const Vector3& a, vec_t b, Vector3& c )
    {
        CHECK_VALID(a);
        ASSERTION( IsFinite(b), "Vector3: infinite!" );
        c.x = a.x * b;
        c.y = a.y * b;
        c.z = a.z * b;
    }
    
    FORCEINLINE void Vector3Multiply( const Vector3& a, const Vector3& b, Vector3& c )
    {
        CHECK_VALID(a);
        CHECK_VALID(b);
        c.x = a.x * b.x;
        c.y = a.y * b.y;
        c.z = a.z * b.z;
    }
    
    // for backwards compatability
    inline void Vector3Scale ( const Vector3& in, vec_t scale, Vector3& result )
    {
        Vector3Multiply( in, scale, result );
    }
    
    
    FORCEINLINE void Vector3Divide( const Vector3& a, vec_t b, Vector3& c )
    {
        CHECK_VALID(a);
        ASSERTION( b != 0.0f, "Vector3: Dividing by zero!" );
        if ( b != 0.0f )
        {
            vec_t oob = 1.0f / b;
            c.x = a.x * oob;
            c.y = a.y * oob;
            c.z = a.z * oob;
        }
    }
    
    FORCEINLINE void Vector3Divide( const Vector3& a, const Vector3& b, Vector3& c )
    {
        CHECK_VALID(a);
        CHECK_VALID(b);
        ASSERTION( (b.x != 0.0f) && (b.y != 0.0f) && (b.z != 0.0f), "VectorDivide: Dividing by zero!" );
        if ( (b.x != 0.0f) && (b.y != 0.0f) && (b.z != 0.0f) )
        {
            c.x = a.x / b.x;
            c.y = a.y / b.y;
            c.z = a.z / b.z;
        }
    }
    
    inline void	Vector3::MulAdd(const Vector3& a, const Vector3& b, float scalar)
    {
        CHECK_VALID(a);
        CHECK_VALID(b);
        x = a.x + b.x * scalar;
        y = a.y + b.y * scalar;
        z = a.z + b.z * scalar;
    }
    
    inline void	Vector3MulAdd(const Vector3 &a, const Vector3 &b, float scalar, Vector3 &dest)
    {
        CHECK_VALID(a);
        CHECK_VALID(b);
        dest.x = a.x + b.x * scalar;
        dest.y = a.y + b.y * scalar;
        dest.z = a.z + b.z * scalar;
    }
    
    inline void Vector3Lerp(const Vector3& src1, const Vector3& src2, vec_t t, Vector3& dest)
    {
        CHECK_VALID(src1);
        CHECK_VALID(src2);
        dest.x = src1.x + (src2.x - src1.x) * t;
        dest.y = src1.y + (src2.y - src1.y) * t;
        dest.z = src1.z + (src2.z - src1.z) * t;
    }
    
    //-----------------------------------------------------------------------------
    // IsValid?
    //-----------------------------------------------------------------------------
    inline bool Vector3::IsValid() const
    {
        return IsFinite(x) && IsFinite(y) && IsFinite(z);
    }
    
    //-----------------------------------------------------------------------------
    // Invalidate
    //-----------------------------------------------------------------------------
    inline void Vector3::Invalidate()
    {
        x = y = z = VEC_T_NAN;
    }
    
    //-----------------------------------------------------------------------------
    // Random Vector Generator
    //-----------------------------------------------------------------------------
    inline void Vector3::Random( vec_t minVal, vec_t maxVal )
    {
        x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
        y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
        z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
        CHECK_VALID(*this);
    }
    
    //-----------------------------------------------------------------------------
    // Zero out vector3
    //-----------------------------------------------------------------------------
    inline void Vector3::Zero()
    {
        x = y = z = 0.0f;
    }
    

    //-----------------------------------------------------------------------------
    // assignment
    //-----------------------------------------------------------------------------
    inline Vector3& Vector3::operator=(const Vector3 &vOther)
    {
        CHECK_VALID(vOther);
        x=vOther.x; y=vOther.y; z=vOther.z;
        return *this;
    }
  #ifdef SLOW_VECTOR_METHODS  
    //-----------------------------------------------------------------------------
    // arithmetic operations
    //-----------------------------------------------------------------------------
    
    inline Vector3 Vector3::operator-(void) const
    {
        return Vector3(-x,-y,-z);
    }
    
    inline Vector3 Vector3::operator+(const Vector3& v) const
    {
        Vector3 res;
        Vector3Add( *this, v, res );
        return res;
    }
    
    inline Vector3 Vector3::operator-(const Vector3& v) const
    {
        Vector3 res;
        Vector3Subtract( *this, v, res );
        return res;
    }
    
    inline Vector3 Vector3::operator*(float fl) const
    {
        Vector3 res;
        Vector3Multiply( *this, fl, res );
        return res;
    }
    
    inline Vector3 Vector3::operator*(const Vector3& v) const
    {
        Vector3 res;
        Vector3Multiply( *this, v, res );
        return res;
    }
    
    inline Vector3 Vector3::operator/(float fl) const
    {
        Vector3 res;
        Vector3Divide( *this, fl, res );
        return res;
    }
    
    inline Vector3 Vector3::operator/(const Vector3& v) const
    {
        Vector3 res;
        Vector3Divide( *this, v, res );
        return res;
    }
    
    inline Vector3 operator*(float fl, const Vector3& v)
    {
        return v * fl;
    }
    
#endif
    
    //-----------------------------------------------------------------------------
    // comparison
    //-----------------------------------------------------------------------------
    FORCEINLINE bool Vector3::operator==( const Vector3& src ) const
    {
        CHECK_VALID(src);
        CHECK_VALID(*this);
        
        return (src.x == x) && (src.y == y) && (src.z == z);
    }
    
    FORCEINLINE bool Vector3::operator!=( const Vector3& src ) const
    {
        CHECK_VALID(src);
        CHECK_VALID(*this);
        return (src.x != x) || (src.y != y) || (src.z != z);
    }
    
    //-----------------------------------------------------------------------------
    // length
    //-----------------------------------------------------------------------------
    inline vec_t VectorLength( const Vector3& v )
    {
        CHECK_VALID(v);
        return (vec_t)sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    }
    
    inline vec_t Vector3::Length(void) const
    {
        CHECK_VALID(*this);
        return VectorLength( *this );
    }
    
    //-----------------------------------------------------------------------------
    // Normalize a vector. ( eq= vec.x / magnitude, vec.y / magnitude, vec.z / magnitude  )
    //-----------------------------------------------------------------------------
    FORCEINLINE float Vector3Normalize( Vector3& v )
    {
        float mag = sqrt( v.x*v.x + v.y*v.y + v.z*v.z );
        
        // Add just a bit to the end of a float so we don't divide by zero.
        float den = 1.f / (mag + FLT_EPSILON );
        v.x *= den;
        v.y *= den;
        v.z *= den;
        
        return mag;
    }
    
    inline vec_t Vector3::NormalizeInPlace()
    {
        return Vector3Normalize( *this );
    }
    
    inline bool Vector3::IsLengthGreaterThan( float val ) const
    {
        return LengthSqr() > val*val;
    }
    
    inline bool Vector3::IsLengthLessThan( float val ) const
    {
        return LengthSqr() < val*val;
    }
    
    //-----------------------------------------------------------------------------
    // Get the distance from this vector to the other one
    //-----------------------------------------------------------------------------
    inline vec_t Vector3::DistTo(const Vector3 &vOther) const
    {
        Vector3 delta;
        Vector3Subtract( *this, vOther, delta );
        return delta.Length();
    }
    
    //-----------------------------------------------------------------------------
    // 2D
    //-----------------------------------------------------------------------------
    
    inline vec_t Vector3::Length2D(void) const
    {
        return (vec_t)sqrt(x*x + y*y);
    }
    
    inline vec_t Vector3::Length2DSqr(void) const
    {
        return (x*x + y*y);
    }
    
    //-----------------------------------------------------------------------------
    // standard math operations
    //-----------------------------------------------------------------------------
    inline void Vector3::Negate()
    {
        CHECK_VALID(*this);
        x = -x; y = -y; z = -z;
    }
    
    FORCEINLINE  Vector3& Vector3::operator+=(const Vector3& v)
    {
        CHECK_VALID(*this);
        CHECK_VALID(v);
        x+=v.x; y+=v.y; z += v.z;
        return *this;
    }
    
    FORCEINLINE  Vector3& Vector3::operator-=(const Vector3& v)
    {
        CHECK_VALID(*this);
        CHECK_VALID(v);
        x-=v.x; y-=v.y; z -= v.z;
        return *this;
    }
    
    FORCEINLINE  Vector3& Vector3::operator*=(float fl)
    {
        x *= fl;
        y *= fl;
        z *= fl;
        CHECK_VALID(*this);
        return *this;
    }
    
    FORCEINLINE  Vector3& Vector3::operator*=(const Vector3& v)
    {
        CHECK_VALID(v);
        x *= v.x;
        y *= v.y;
        z *= v.z;
        CHECK_VALID(*this);
        return *this;
    }
    
    // this ought to be an opcode.
    FORCEINLINE Vector3&	Vector3::operator+=(float fl)
    {
        x += fl;
        y += fl;
        z += fl;
        CHECK_VALID(*this);
        return *this;
    }
    
    FORCEINLINE Vector3&	Vector3::operator-=(float fl)
    {
        x -= fl;
        y -= fl;
        z -= fl;
        CHECK_VALID(*this);
        return *this;
    }
    
    
    
    FORCEINLINE  Vector3& Vector3::operator/=(float fl)
    {
        ASSERTION( fl != 0.0f, "Vector3: Dividing by zero!" );
        float oofl = 1.0f / fl;
        x *= oofl;
        y *= oofl;
        z *= oofl;
        CHECK_VALID(*this);
        return *this;
    }
    
    FORCEINLINE  Vector3& Vector3::operator/=(const Vector3& v)
    {
        CHECK_VALID(v);
        ASSERTION( v.x != 0.0f && v.y != 0.0f && v.z != 0.0f, "Vector3: Dividing by zero!" );
        x /= v.x;
        y /= v.y;
        z /= v.z;
        CHECK_VALID(*this);
        return *this;
    }
    
    void LookAtToAxes(const Vector3& pos, const Vector3& target, const Vector3& upDir,
                      Vector3& left, Vector3& up, Vector3& forward);
    
    extern const Vector3 Vector3Origin;
    
    //=========================================================
    // 2D Vector
    //=========================================================
    class Vector2
    {
    public:
        // Members
        vec_t x, y;
        
        // Construction/destruction:
        Vector2()
        {
#ifdef _DEBUG
            // Initialize to NAN to catch errors
            x = y = VEC_T_NAN;
#endif
        }
        
        Vector2(vec_t X, vec_t Y)
        {
            x = X; y = Y;
            CHECK_VALID(*this);
        }
        
        // Initialization
        void Init(vec_t ix=0.0f, vec_t iy=0.0f)
        {
            x=ix;
            y=iy;
        }
        
        void Init(int ix=0, int iy=0)
        {
            x=(float)ix;
            y=(float)iy;
        }
        
        // Got any nasty NAN's?
        bool IsValid() const;
        void Invalidate();
        
        void Random( vec_t minVal, vec_t maxVal );
        
        // Initialization methods
        void Zero(); ///< zero out a vector
        
        void Negate();
        
        FORCEINLINE Vector2&	operator=(const Vector2 &vOther);
        
        // equality
        bool operator==(const Vector2& v) const;
        bool operator!=(const Vector2& v) const;
        
        // arithmetic operations
        FORCEINLINE Vector2&	operator+=(const Vector2 &v);
        FORCEINLINE Vector2&	operator-=(const Vector2 &v);
        FORCEINLINE Vector2&	operator*=(const Vector2 &v);
        FORCEINLINE Vector2&	operator*=(float s);
        FORCEINLINE Vector2&	operator/=(const Vector2 &v);
        FORCEINLINE Vector2&	operator/=(float s);
        FORCEINLINE Vector2&	operator+=(float fl) ; ///< broadcast add
        FORCEINLINE Vector2&	operator-=(float fl) ; ///< broadcast sub
    };
    
    extern const Vector2 Vector2Origin;
    
    //-----------------------------------------------------------------------------
    // IsValid?
    //-----------------------------------------------------------------------------
    inline bool Vector2::IsValid() const
    {
        return IsFinite(x) && IsFinite(y);
    }
    
    //-----------------------------------------------------------------------------
    // Invalidate
    //-----------------------------------------------------------------------------
    inline void Vector2::Invalidate()
    {
        x = y = VEC_T_NAN;
    }
    
    //-----------------------------------------------------------------------------
    // Random Vector Generator
    //-----------------------------------------------------------------------------
    inline void Vector2::Random( vec_t minVal, vec_t maxVal )
    {
        x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
        y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
        CHECK_VALID(*this);
    }
    
    //-----------------------------------------------------------------------------
    // Zero out vector3
    //-----------------------------------------------------------------------------
    inline void Vector2::Zero()
    {
        x = y = 0.0f;
    }
    
    //-----------------------------------------------------------------------------
    // assignment
    //-----------------------------------------------------------------------------
    inline Vector2& Vector2::operator=(const Vector2 &vOther)	
    {
        CHECK_VALID(vOther);
        x=vOther.x; y=vOther.y;
        return *this;
    }
    
    //-----------------------------------------------------------------------------
    // comparison
    //-----------------------------------------------------------------------------
    inline bool Vector2::operator==( const Vector2& src ) const
    {
        CHECK_VALID(src);
        CHECK_VALID(*this);
        return (src.x == x) && (src.y == y);
    }
    
    inline bool Vector2::operator!=( const Vector2& src ) const
    {
        CHECK_VALID(src);
        CHECK_VALID(*this);
        return (src.x != x) || (src.y != y);
    }
    
    //-----------------------------------------------------------------------------
    // standard math operations
    //-----------------------------------------------------------------------------
    inline void Vector2::Negate()
    { 
        CHECK_VALID(*this);
        x = -x; y = -y;
    } 
    
    FORCEINLINE  Vector2& Vector2::operator+=(const Vector2& v)	
    { 
        CHECK_VALID(*this);
        CHECK_VALID(v);
        x+=v.x; y+=v.y;	
        return *this;
    }
    
    FORCEINLINE  Vector2& Vector2::operator-=(const Vector2& v)	
    { 
        CHECK_VALID(*this);
        CHECK_VALID(v);
        x-=v.x; y-=v.y;	
        return *this;
    }
    
    FORCEINLINE  Vector2& Vector2::operator*=(float fl)	
    {
        x *= fl;
        y *= fl;
        CHECK_VALID(*this);
        return *this;
    }
    
    FORCEINLINE  Vector2& Vector2::operator*=(const Vector2& v)	
    { 
        CHECK_VALID(v);
        x *= v.x;
        y *= v.y;
        CHECK_VALID(*this);
        return *this;
    }
    
    // this ought to be an opcode.
    FORCEINLINE Vector2&	Vector2::operator+=(float fl) 
    {
        x += fl;
        y += fl;
        CHECK_VALID(*this);
        return *this;
    }
    
    FORCEINLINE Vector2&	Vector2::operator-=(float fl) 
    {
        x -= fl;
        y -= fl;
        CHECK_VALID(*this);
        return *this;
    }
    
    FORCEINLINE  Vector2& Vector2::operator/=(float fl)	
    {
        ASSERTION( fl != 0.0f, "Vector2: Dividing by zero!" );
        float oofl = 1.0f / fl;
        x *= oofl;
        y *= oofl;
        CHECK_VALID(*this);
        return *this;
    }
    
    FORCEINLINE  Vector2& Vector2::operator/=(const Vector2& v)	
    {
        CHECK_VALID(v);
        ASSERTION( v.x != 0.0f && v.y != 0.0f, "Vector2: Dividing by zero!" );
        x /= v.x;
        y /= v.y;
        CHECK_VALID(*this);
        return *this;
    }
    
    //=========================================================
    // Integer based vector 2
    //=========================================================
    class IntegerVector2
    {
    public:
        // Members
        int x, y;
        
        // Construction/destruction:
        IntegerVector2(){ }
        IntegerVector2(int X, int Y)
        {
            x = X; y = Y;
        }
        
        // Initialization
        void Init( int ix = 0, int iy = 0 )
        {
            x = ix;
            y = iy;
        }
        
        IntegerVector2& operator=(const IntegerVector2 &vOther)
        {
            x = vOther.x;
            y = vOther.y;
            return *this;
        }
    };
    
} // namespace mathLib

#endif // MATH_VECTOR_H