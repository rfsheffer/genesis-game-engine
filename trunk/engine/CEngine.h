//
//  CEngine.h
//  The lowest level of a running game, works with the extensions manager to
//  run the application as designed by the developer.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CENGINE_H
#define CENGINE_H

#include "CExtensions.h"

class CEngine
{
public:
    bool        m_bHaultExecution;
    
    void        Initialize(void);
    void        Run(void);
    void        Shutdown(void);
    
private:
    
    CExtensions     *m_pExtensionManager;
};

#endif // CENGINE_H
