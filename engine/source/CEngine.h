//
//  CEngine.h
//  The lowest level of a running genesis program, works with the extensions
//  manager to run the application as designed by the developer.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CENGINE_H
#define CENGINE_H

#include "IEngine.h"
#include "CExtensions.h"
#include "CEngineClient.h"
#include "AppVariables.h"

// Index 0 is always the local engine.
#define LOCAL_ENGINE_CLIENT_INDEX       0

// TODO: We are temporarily only allowing a single client, but that will change.
#define MAX_ENGINE_CLIENTS              1

/** The engine which drives the extensions manager. */
class CEngine : public IEngine
{
public:
    
    void        Initialize(void);
    void        Run(void);
    void        Shutdown(void);
    bool        FinishedExecution(void) { return m_bHaultExecution; }
    
    /** Get the extensions manager which created this extension. */
    IExtensions     *GetExtensions(void){ return m_pExtensionManager; }
    
private:
    
    /** If true, the engine has been requested to hault. This will terminate
     * the programs execution. */
    bool        m_bHaultExecution;
    
    /** The extensions manager to drive. */
    IExtensions     *m_pExtensionManager;
    
    CEngineClient   m_EngineClients[MAX_ENGINE_CLIENTS];
};

CEngine     *GetEngine(void);

#endif // CENGINE_H
