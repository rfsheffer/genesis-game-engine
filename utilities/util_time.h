//
//  util_time.h
//  A class used for telling application time
//
//  Created by Ryan Sheffer on 2012-11-17.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_TIME_H
#define UTIL_TIME_H

#pragma once

#if defined(_WIN)

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#elif defined(_MAC)

#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h>

#endif

namespace Utility
{
    /** Timer States */
    enum TIMER_STATES_E
    {
        TIMER_STATE_INVALID,
        TIMER_STATE_STARTED,
        TIMER_STATE_ENDED
    };
    
    class CTime
    {
    public:
        
        CTime();
        ~CTime() { }
        
        void Init();
        void Update();
        
        /** Gets the current time in nanoseconds */
        inline uint64_t GetPerfTime() const
        {
            return m_ui64AccumTime;
        }
        
        /** Gets the elapsed nanoseconds since last update call */
        inline uint64_t GetPerfElapsedTime() const
        {
            return m_ui64ElapsedTime;
        }
        
        /** Gets the system time in nanoseconds */
        inline uint64_t GetPerfSystemTime() const
        {
            return m_ui64CurTime;
        }
        
    private:
        
        /** The system time when the program started time */
        uint64_t            m_ui64StartTime;
        
        /** Current system time */
        uint64_t            m_ui64CurTime;
        
        /** 
         * This is the time in nanoseconds from when the program started
         * to the current time.
         */
        uint64_t			m_ui64AccumTime;
        
        /** This is the time since the last call to the GetElapsedTime */
        uint64_t			m_ui64ElapsedTime;
        
        /** This is the time when GetElapsedTime was last called. */
        uint64_t			m_ui64LastAccumTime;
        
        /** Using the CPU performance timer? */
        bool			m_bPerformance_Timer;
    };
    
    double ConvertToSeconds(uint64_t perfTime);
    uint64_t ConvertToCycles(double time);
}

#endif // UTIL_TIME_H