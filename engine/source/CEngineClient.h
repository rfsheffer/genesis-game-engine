//
//  CEngineClient.h
//  Engine Client Data
//
//  Created by Ryan Sheffer on 2013-02-05.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef C_ENGINE_CLIENT
#define C_ENGINE_CLIENT

#ifdef _WIN
#pragma once
#endif

/**
 * This is an engine client. When an engine is in control of a number of
 * other engines via a network, the engine will contain a list of engine
 * clients. Extensions can take advantage of this by sending data to other
 * engine clients directly or to an engine clients extension managers extension.
 */
class CEngineClient
{
public:
    
    /** Constructor */
    CEngineClient() : m_sClientFlags(ECF_EMPTY) {}
    
    /** Engine Client Flags */
    enum e_client_flags
    {
        /** Un-initialized */
        ECF_EMPTY           = 0,
        
        /** Local client */
        ECF_LOCAL_CLIENT    = 0x01,
        
        /** Network Client */
        ECF_NETWORK_CLIENT  = 0x02
    };
    
    /** This engine clients info flags */
    short   m_sClientFlags;
    
    /** Initialize a local engine client */
    void    InitializeLocal(void)
    {
        m_sClientFlags = ECF_LOCAL_CLIENT;
    }
    
    /** Initalize a network engine client */
    void    InitializeNetwork(void)
    {
        m_sClientFlags = ECF_NETWORK_CLIENT;
    }
};

#endif // C_ENGINE_CLIENT
