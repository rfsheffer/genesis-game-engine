//
//  variant.h
//  A class designed to act as a smart variable holder. It holds a union of
//  a number of common types, and contains a number of methods for converting
//  between types.
//
//  Created by Ryan Sheffer on 2013-04-22.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef VARIANT_H
#define VARIANT_H

#include "floatwatch.h"
#include "data/data_types.h"

namespace Utility
{
    //--------------------------------------------------------------------------
    /** Variant type, multiple types, one object */
    class Variant
    {
    public:
        
        /** The union of this variant */
        union
        {
            void        *pData;
            bool        bVal;
            int         iVal;
            float       flVal;
            short       sVal;
            const char  *pszVal;
        } m_val;
        
        Variant()
        {
            type = DATA_INTEGER;
            m_val.iVal = 0;
        }
        
        /** The type of data this variant thinks it wraps */
        data_types type;
        
        void                SetFromString(const char *pszString);
        
        /** Gets the boolean value of this variant */
        inline bool         GetBool(void) const { return m_val.bVal; }
        
        /** Gets the integer value of this variant */
        inline int          GetInt(void) const { return m_val.iVal; }
        
        /** Get the float value of the variant */
        inline float        GetFloat(void) const { return m_val.flVal; }
        
        /** Sets the boolean contained in this variant */
        inline void         SetBool(bool val){ m_val.bVal = val; }
        
        /** Sets the integer contained in this variant */
        inline void         SetInt(int val){ m_val.iVal = val; }
        
        /** Sets the float contained in this variant */
        inline void         SetFloat(float val) { m_val.flVal = val; }
        
        const char          *ToString(void) const;
    };
    
    //--------------------------------------------------------------------------
    /** A derivation of Variant for math types */
    /** NOTE: This shouldn't be used. I am still deciding how I want to do types
     *        like matrix, quaternion and vector */
    class MathVariant
    {
    public:
        /** The union of this variant */
        union
        {

            float       flVal2[2];      // Vec2
            float       flVal3[3];      // Vec3
            float       flVal4[4];      // Vec4
            float       flVal9[9];      // Vec9
            float       flVal16[16];    // Vec16
        } m_mathval;
        
        /**
         * Gets a pointer to the start of the union, which can contain up to
         * 16 floating point variables. Can represent a matrix or a vector.
         */
        inline const float  *GetVector(void) const { return m_mathval.flVal2; }
        
        /**
         * Sets the vector elements contained in this variant
         * @param pVec The contiguous float data representing a vector or matrix
         * @param numComps The number of floats at pVec
         */
        inline void         SetVector(const float *pVec, unsigned int numComps)
        {
            ASSERTION(numComps <= 16, "Variant: Setting a vector with an unsupported number of components.");
            
            for(int i = 0; i < numComps; ++i)
            {
                m_mathval.flVal2[i] = pVec[i];
            }
        }
    };
};

#endif // VARIANT_H
