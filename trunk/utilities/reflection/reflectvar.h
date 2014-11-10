//
//  reflectvar.h
//  utilities
//
//  Created by Ryan Sheffer on 2014-11-09.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef utilities_reflectvar_h
#define utilities_reflectvar_h

class ReflectVarInterface
{
public:
    virtual reflect_types  GetType(void) const = 0;
    virtual const char  *GetName(void) const = 0;
};

//------------------------------------------------------------------------------
/** A reflected Variable (base class to non-pod types) */
template<class T, reflect_types datatype>
class ReflectVar : public ReflectVarInterface
{
public:
    /** Initialized the variable information */
    ReflectVar(const char *pszVarName, unsigned int offset)
    {
        
    }
    
    /** Returns the type of variable is reflected here */
    reflect_types GetType(void) const { return datatype; }
    
    /** Gets the name associated with this variable */
    const char  *GetName(void) const { return m_name.m_pszPoolString; }
    
private:
    
    /** The name of the var */
    Utility::CString        m_name;
    
    /** The offset into the class */
    unsigned int            m_offset;
};


#endif
