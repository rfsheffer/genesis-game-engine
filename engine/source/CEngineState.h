//
//  CEngineState.h
//  This is included in the platforms application code to keep a state of the
//  engine.
//
//  Created by Ryan Sheffer on 2013-04-12.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef ENGINE_STATE_H
#define ENGINE_STATE_H

class CEngineState
{
public:
    /**
     * The current running state of the engine
     */
    enum engine_state
    {
        ENGINE_STATE_RUNNING,
        ENGINE_STATE_LOCKED,
        ENGINE_STATE_CLOSED
    };
    
    /**
     * The reason for locking the engine from running
     */
    enum engine_lock_reason
    {
        ENGINE_UNLOCKED,
        ENGINE_LOCK_WAIT,
        ENGINE_LOCK_QUIT
    };
    
    /** 
     * This is a way for the application to talk with the main loop thread.
     * The application can hault the main loop thread for some reason, or use
     * this to quit execution of the engine.
     */
    static engine_lock_reason      engineLockReason;
    static engine_state            enginestate;
};

CEngineState::engine_lock_reason CEngineState::engineLockReason = CEngineState::ENGINE_UNLOCKED;
CEngineState::engine_state CEngineState::enginestate = CEngineState::ENGINE_STATE_CLOSED;

#endif // ENGINE_STATE_H
