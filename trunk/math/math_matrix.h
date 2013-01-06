//
//  math_matrix.h
//  Matrix Classes
//
//  Created by Ryan Sheffer on 2012-11-10.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef MATH_MATRIX
#define MATH_MATRIX

namespace MathLib
{
    
    /* MATRIX ORDER - Column Ordering
     
     x         y          z          w
     m_elms[0] m_elms[4] m_elms[8]  m_elms[12]
     m_elms[1] m_elms[5] m_elms[9]  m_elms[13]
     m_elms[2] m_elms[6] m_elms[10] m_elms[14]
     m_elms[3] m_elms[7] m_elms[11] m_elms[15]
     
     */
    
    //-----------------------------------------------------------------------------
    // 4x4 Matrix
    //-----------------------------------------------------------------------------
    class matrix4x4
    {
    public:
        vec_t m_elms[16];
        
        // For getting a pointer to the first element.
        // Useful for passing the matrix into an API
        // such as the graphics API.
        inline vec_t *Base()
        {
            return &m_elms[0];
        }
        inline const vec_t *Base() const
        {
            return &m_elms[0];
        }
        
        vec_t operator[](int i) const
        {
            return m_elms[i];
        }
        vec_t& operator[](int i)
        {
            return m_elms[i];
        }
        
        inline void Identity(void);
        inline void Transpose(void);
        
        inline void SetTranslation(const Vector3 &vTrans);
        inline void SetTranslation(float x, float y, float z);
        inline void GetTranslation(Vector3 &vTrans) const;
        
        // Rotation
        inline void SetRotationX(float theta);
        inline void SetRotationY(float theta);
        inline void SetRotationZ(float theta);
        
        void	GetBasisVectors(Vector3 &vLeft, Vector3 &vUp, Vector3 &vForward) const;
        
        // Operators
        bool		operator==( const matrix4x4& src ) const;
        bool		operator!=( const matrix4x4& src ) const { return !( *this == src ); }
    };
    
    //-----------------------------------------------------------------------------
    // Purpose: Sets to Identity
    //-----------------------------------------------------------------------------
    inline void matrix4x4::Identity(void)
    {
        m_elms[0] = 1;	m_elms[4] = 0;	m_elms[8] = 0;	m_elms[12] = 0;
        m_elms[1] = 0;	m_elms[5] = 1;	m_elms[9] = 0;	m_elms[13] = 0;
        m_elms[2] = 0;	m_elms[6] = 0;	m_elms[10] = 1;	m_elms[14] = 0;
        m_elms[3] = 0;	m_elms[7] = 0;	m_elms[11] = 0;	m_elms[15] = 1;
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Transpose the Matrix ( Flips Column to Row Major and Vice Versa )
    //-----------------------------------------------------------------------------
    inline void matrix4x4::Transpose(void)
    {
        float temp;
        // 1
        temp = m_elms[1];
        m_elms[1] = m_elms[4]; m_elms[4] = temp;
        
        temp = m_elms[2];
        m_elms[2] = m_elms[8]; m_elms[8] = temp;
        
        temp = m_elms[3];
        m_elms[3] = m_elms[12]; m_elms[12] = temp;
        
        // 2
        temp = m_elms[6];
        m_elms[6] = m_elms[9]; m_elms[9] = temp;
        
        temp = m_elms[7];
        m_elms[7] = m_elms[13]; m_elms[13] = temp;
        
        // 3
        temp = m_elms[11];
        m_elms[11] = m_elms[14]; m_elms[14] = temp;
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Sets the translation column of the matrix
    //-----------------------------------------------------------------------------
    inline void matrix4x4::SetTranslation(const Vector3 &vTrans)
    {
        m_elms[12] = vTrans.x;	m_elms[13] = vTrans.y;	m_elms[14] = vTrans.z;
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Sets the translation column of the matrix
    //-----------------------------------------------------------------------------
    inline void matrix4x4::SetTranslation(float x, float y, float z)
    {
        m_elms[12] = x;	m_elms[13] = y;	m_elms[14] = z;
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Gets the translation column of the matrix
    //-----------------------------------------------------------------------------
    inline void matrix4x4::GetTranslation(Vector3 &vTrans) const
    {
        vTrans.x = m_elms[12]; vTrans.y = m_elms[13]; vTrans.z = m_elms[14];
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Sets a single rotation for the entire matrix, clearing any previous data
    //-----------------------------------------------------------------------------
    inline void matrix4x4::SetRotationX(float theta)
    {
        Identity();
        
        float s, c;
        SinCos(theta, &s, &c);
        
        m_elms[5] = c;	m_elms[9] = -s;
        m_elms[6] = s;	m_elms[10] = c;
    }
    
    inline void matrix4x4::SetRotationY(float theta)
    {
        Identity();
        
        float s, c;
        SinCos(theta, &s, &c);
        
        m_elms[0] = c;	m_elms[8] = s;
        m_elms[2] = -s;	m_elms[10] = c;
    }
    
    inline void matrix4x4::SetRotationZ(float theta)
    {
        Identity();
        
        float s, c;
        SinCos(theta, &s, &c);
        
        m_elms[0] = c;	m_elms[4] = -s;
        m_elms[1] = s;	m_elms[5] = c;
    }
    
    //-----------------------------------------------------------------------------
    // Declared in math_matrix.cpp
    //-----------------------------------------------------------------------------
    void MatrixMultiply(matrix4x4 &in1, matrix4x4 &in2, matrix4x4 &out);
    
} // namespace mathLib

#endif