//
//  Interfaces.h
//  This is a place to pool pointers to interfaces. The other libraries can
//  get useful interfaces by pointer here.
//
//  Created by Ryan Sheffer on 2/5/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef INTERFACES_H
#define INTERFACES_H

#ifdef _WIN
#pragma once
#endif

typedef void *(*InterfaceGetFunc)(void);
typedef void  (*InterfaceKillFunc)(void *);

// This is so we can keep track of all
struct InterfacePointer
{
    void                        *pPointer;
    InterfacePointer            *pNext;
};

//------------------------------------------------------------------------------
/**
 * The interface holder
 */
class InterfaceElement
{
public:
    
    InterfaceElement(InterfaceGetFunc func,
                     InterfaceKillFunc killFunc,
                     const char *pszElementName,
                     int version,
                     bool isStatic);
    
    InterfaceElement            *m_pNext;
    InterfaceGetFunc            m_getFunc;
    InterfaceKillFunc           m_killFunc;
    
    /** When interfaces are created we save off the pointers so we can keep track
     * of those pesky programmers forgetting to free their memory! ;) */
    InterfacePointer        *m_pInterfacePointer;
    
    const char *m_pszElementName;
    int         m_iVersion;
    
    /** Will this element create multiple new memory elements? */
    bool        m_bIsStatic;
};

//------------------------------------------------------------------------------
/**
 * Class which holds interface pointers and registration methods
 */
class InterfaceRegistration
{
public:
    
    InterfaceRegistration();
    
    void RegisterInterface(InterfaceElement *pNewElement);
    void *GetInterface(const char *pszName, int version);
    
    void ReleaseInterfacePointer(const char *pszName, void *pInterfacePointer);
    
    void ReleaseAllInterfacePointers(void);
    
private:
    InterfaceElement *m_pHead;
};

InterfaceRegistration *GetInterfaceRegistration(void);

// Use this to register a function which returns a pointer to static memory
#define REGISTER_STATIC_INTERFACE_FUNC(func, name, version) \
            static InterfaceElement    _interfaceFunc##func(func, NULL, name, version, true);

// Use this to register a function which returns a pointer to dynamic memory
#define REGISTER_DYNAMIC_INTERFACE_FUNC(createfunc, destroyfunc, name, version) \
            static InterfaceElement    _interfaceFunc##func(createfunc, destroyfunc, name, version, false);

#define REGISTER_STATIC_INTERFACE(singleton, name, version) \
            void *_interface##singleton##func(void) { return &singleton; } \
            REGISTER_STATIC_INTERFACE_FUNC(_interface##singleton##func, name, version)

#endif // INTERFACES_H
