//
//  Interfaces.cpp
//  This is a place to pool pointers to interfaces. The other libraries can
//  get useful interfaces by pointer here.
//
//  Created by Ryan Sheffer on 2/5/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "allhead.h"
#include "interfaces.h"

static InterfaceRegistration g_interfaceRegistration;

/**
 * Gets the interface registar singleton. Primary access from external sources.
 */
InterfaceRegistration *GetInterfaceRegistration(void)
{
    return &g_interfaceRegistration;
}

//------------------------------------------------------------------------------
/**
 * Constructs an Interface Element
 * @param func Function for getting or creating the interface class
 * @param killFunc Function only used for dynamic interfaces to help kill the memory allocation
 * @param pszElementName Interface name
 * @param version The version of this interface, used to detect usage of old interfaces
 * @param isStatic True if this interface is static (single interface)
 */
InterfaceElement::InterfaceElement(InterfaceGetFunc func,
                                   InterfaceKillFunc killFunc,
                                   const char *pszElementName,
                                   int version,
                                   bool isStatic)
{
    ASSERTION(isStatic == true || (isStatic == false && killFunc != NULL),
              "Dynamic interface %s missing kill function!", pszElementName);
    
    m_getFunc = func;
    m_killFunc = killFunc;
    m_pszElementName = pszElementName;
    m_iVersion = version;
    m_bIsStatic = isStatic;
    m_pInterfacePointer = NULL;
    GetInterfaceRegistration()->RegisterInterface(this);
}

//------------------------------------------------------------------------------
/**
 * Constructor
 */
InterfaceRegistration::InterfaceRegistration()
{
    m_pHead = NULL;
}

//------------------------------------------------------------------------------
/**
 * Registers an interface
 */
void InterfaceRegistration::RegisterInterface(InterfaceElement *pNewElement)
{
    ASSERTION(pNewElement, "Invalid Interface Pointer!");
    ASSERTION(!GetInterface(pNewElement->m_pszElementName, pNewElement->m_iVersion),
              "Adding the same interface twice!");
    
    pNewElement->m_pNext = m_pHead;
    m_pHead = pNewElement;
}

//------------------------------------------------------------------------------
/**
 * Gets an interface pointer by name
 */
void *InterfaceRegistration::GetInterface(const char *pszName, int version)
{
    InterfaceElement *pCur = m_pHead;
    while(pCur)
    {
        if(util_stricmp(pCur->m_pszElementName, pszName) == 0)
        {
            ASSERTION((pCur->m_iVersion == version || version == -1),
                      "Version mismatch for interface! Probably needs to update.");
            
            void *pReturned = pCur->m_getFunc();
            
            // If this isn't a static interface, we keep a watch on the interface
            // elements in debug and report un-released stuff on program shutdown.
            if(!pCur->m_bIsStatic)
            {
                if(pCur->m_pInterfacePointer == NULL)
                {
                    pCur->m_pInterfacePointer = new InterfacePointer;
                    pCur->m_pInterfacePointer->pNext = NULL;
                    pCur->m_pInterfacePointer->pPointer = pReturned;
                }
                else
                {
                    // Need to check if the pointer returned is the same as
                    // one of the pointers already stored.
                    InterfacePointer *pCurIntPnt = pCur->m_pInterfacePointer;
                    InterfacePointer *pLastIntPnt = NULL;
                    for(;;) // while(true)
                    {
                        if(pCurIntPnt->pPointer == pReturned)
                        {
                            break;
                        }
                        
                        if(pCurIntPnt->pNext == NULL)
                        {
                            pLastIntPnt = pCurIntPnt;
                            break;
                        }
                        
                        pCurIntPnt = pCurIntPnt->pNext;
                    }
                    
                    if(pLastIntPnt)
                    {
                        pLastIntPnt->pNext = new InterfacePointer;
                        pLastIntPnt->pNext->pNext = NULL;
                        pLastIntPnt->pNext->pPointer = pReturned;
                    }
                }
            }
            
            return pReturned;
        }
        
        pCur = pCur->m_pNext;
    }
    
    return NULL;
}

//------------------------------------------------------------------------------
/**
 * Releases a specific interface pointer. It is expected that the actual pointer
 * was properly released as well. This is to release the debug information.
 */
void InterfaceRegistration::ReleaseInterfacePointer(const char *pszName, void *pInterfacePointer)
{
    InterfaceElement *pCur = m_pHead;
    while(pCur)
    {
        if(util_stricmp(pCur->m_pszElementName, pszName) == 0)
        {
            InterfacePointer *pCurIntPnt = pCur->m_pInterfacePointer;
            if(!pCurIntPnt)
            {
                return;
            }
            
            if(pCurIntPnt->pPointer == pInterfacePointer)
            {
                // It was the first element, set to next and be done
                pCur->m_pInterfacePointer = pCurIntPnt->pNext;
                
                // Fire the kill callback
                pCur->m_killFunc(pCurIntPnt->pPointer);
                
                delete pCurIntPnt;
                return;
            }
            
            for(;;) // while(true)
            {
                if(!pCurIntPnt->pNext)
                {
                    break;
                }
                
                if(pCurIntPnt->pNext->pPointer == pInterfacePointer)
                {
                    InterfacePointer *pTemp = pCurIntPnt->pNext;
                    pCurIntPnt->pNext = pCurIntPnt->pNext->pNext;
                    
                    // Fire the kill callback
                    pCur->m_killFunc(pTemp->pPointer);
                    
                    delete pTemp;
                    break;
                }
                
                pCurIntPnt = pCurIntPnt->pNext;
            }
            
            return;
        }
        
        pCur = pCur->m_pNext;
    }
}

//------------------------------------------------------------------------------
/**
 * Releases all interfaces
 */
void InterfaceRegistration::ReleaseAllInterfacePointers(void)
{
    InterfaceElement *pCur = m_pHead;
    while(pCur)
    {
        InterfacePointer *pCurIntPnt = pCur->m_pInterfacePointer;
        InterfacePointer *pTemp = NULL;
        while(pCurIntPnt)
        {
            if(pCurIntPnt->pPointer)
            {
                // Fire the kill callback and post an error message
                pCur->m_killFunc(pCurIntPnt->pPointer);
                
                ASSERTION_ALWAYS("Un-released interface pointer of %s!", pCur->m_pszElementName);
                Logging::Warning("Interface Warning: unreleased dynamic interface of %s!\n",
                        pCur->m_pszElementName);
            }
            
            pTemp = pCurIntPnt;
            pCurIntPnt = pCurIntPnt->pNext;
            delete pTemp;
        }
        
        pCur->m_pInterfacePointer = NULL;
        pCur = pCur->m_pNext;
    }
}