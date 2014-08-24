//
//  VariableWrappers.h
//  scripting
//
//  Created by Ryan Sheffer on 2014-08-23.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef scripting_VariableWrappers_h
#define scripting_VariableWrappers_h

class ReflectType
{
public:
    ReflectType(data_types type) {m_type = type;}
    data_types m_type;
};

template<class T, data_types datatype>
class ReflectVariable : public ReflectType
{
public:
    ReflectVariable() : ReflectType(datatype){}
    
    const void* GetPointer(void)
    {
        return (const void*)&m_var;
    }
    
    const T& Get(void)
    {
        return m_var;
    }
    
    T& GetForModify(void)
    {
        return m_var;
    }
    
    T m_var;
};

#endif
