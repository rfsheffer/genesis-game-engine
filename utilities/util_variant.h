//
//  util_variant.h
//  launcher
//
//  Created by Ryan Sheffer on 2013-04-22.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_VARIANT_H
#define UTIL_VARIANT_H

namespace Utility
{
    //--------------------------------------------------------------------------
    /** Variant type, multiple types, one object */
    template<int VAR_LEN = 64>
    class Variant
    {
    public:        
        /** The union of this variant */
        union
        {
            bool        bVal;
            
            char        szVal[VAR_LEN];
            
            int         iVal;
            float       flVal;
        } m_val;
        
        /** Gets the string value of this variant */
        inline const char   *GetString(void) const { return m_val.szVal; }
        
        /** Gets the boolean value of this variant */
        inline bool         GetBool(void) const { return m_val.bVal; }
        
        /** Gets the integer value of this variant */
        inline int          GetInt(void) const { return m_val.iVal; }
        
        /** Get the float value of the variant */
        inline float        GetFloat(void) const { return m_val.flVal; }
        
        /** Sets the integer contained in this variant */
        inline void         SetInt(int val){ m_val.iVal = val; }
        
        /** Sets the float contained in this variant */
        inline void         SetFloat(float val) { m_val.flVal = val; }
        
        /** Sets the string contained in this variant */
        inline void         SetString(const char *pszString);
        
        const char          *ToString(void) const;
    };
    
    //--------------------------------------------------------------------------
    /** Sets the string contained in this variant to pszString */
    template<int VAR_LEN>
    inline void         Variant<VAR_LEN>::SetString(const char *pszString)
    {
        ASSERTION((strlen(pszString) + 1) <= VAR_LEN,
                  "Variant:: Setting a string which is too large for this variants size.");
        
        // This will pad the remaining with zeros...
        strncpy(m_val.szVal, pszString, VAR_LEN);
    }
    
    //--------------------------------------------------------------------------
    /** A derivation of Variant for math types */
    template<int VAR_LEN = 64>
    class MathVariant : public Variant<VAR_LEN>
    {
    public:
        /** The union of this variant */
        union
        {

            float       flval2[2];      // Vec2
            float       flVal3[3];      // Vec3
            float       flVal4[4];      // Vec4
            float       flVal9[9];      // Vec9
            float       flVal16[16];    // Vec16
        } m_mathval;
        
        /**
         * Gets a pointer to the start of the union, which can contain up to
         * 16 floating point variables. Can represent a matrix or a vector.
         */
        inline const float  *GetVector(void) const { return &m_mathval.flVal2; }
        
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
                (&(m_mathval.flval2))[i] = pVec[i];
            }
        }
    };
};

#endif // UTIL_VARIANT_H
