//
//  Reflected.cpp
//  scripting
//
//  Created by Ryan Sheffer on 2014-08-23.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "scripthead.h"
#include "Reflected.h"
#include "memory/memory_interface.h"

//------------------------------------------------------------------------------
/**
 * Tests the reflected classes
 */
void TestReflectedClasses(void)
{
    // Initialize the memory pool for usage
    GetMemoryPool()->Initialize();
    
    ReflectedClass *pClassTest = new ReflectedClass();
    
    ReflectClass *pMap = pClassTest->Init(NULL);
    
    pMap->PrintMap();
    
    delete pClassTest;
}

//------------------------------------------------------------------------------
ReflectClass *BaseReflected::Init(ReflectClass *pNextClass)
{
    // Setup my enumeration mapping for serialization
    EnumMapping *enumMap = EnumMap::AddMapping("Reflected", "testenum");
    enumMap->AddRow("ENUM_ELEM_1", testenum::ENUM_ELEM_1);
    enumMap->AddRow("ENUM_ELEM_2", testenum::ENUM_ELEM_2);
    enumMap->AddRow("ENUM_ELEM_3", testenum::ENUM_ELEM_3);
    enumMap->AddRow("ENUM_ELEM_4", testenum::ENUM_ELEM_4);
    
    ReflectClass *pMyClassMap = new ReflectClass("BaseReflected");
    pMyClassMap->m_pNext = pNextClass;
    
    ReflectEnum<testenum, REFLECT_ENUM> *p_myEnum =
    new ReflectEnum<testenum, REFLECT_ENUM>("myEnum", offsetof(BaseReflected, myEnum), enumMap);
    pMyClassMap->AddReflected(p_myEnum);
    
    return pMyClassMap;
}

//------------------------------------------------------------------------------
ReflectClass *ReflectedClass::Init(ReflectClass *pNextClass)
{
    ReflectClass *pMyClassMap = new ReflectClass("ReflectedClass");
    pMyClassMap->m_pNext = pNextClass;
    
    ReflectVar<int, REFLECT_POD> *pmember3 =
    new ReflectVar<int, REFLECT_POD>("member3", offsetof(ReflectedClass, member3));
    pMyClassMap->AddReflected(pmember3);
    
    ReflectStruct<ReflectedComponent, REFLECT_STRUCT> *pmember5 =
    new ReflectStruct<ReflectedComponent, REFLECT_STRUCT>("member5", offsetof(ReflectedClass, member5));
    pMyClassMap->AddReflected(pmember5);
    
    return BaseReflected::Init(pMyClassMap);
}