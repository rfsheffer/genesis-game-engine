//
//  util_perf_timer.h
//  This is a performance timer for high resolution and precise timing. Good
//  for timing operations which run very fast.
//
//  Created by Ryan Sheffer on 2012-11-18.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_PERF_TIMER_H
#define UTIL_PERF_TIMER_H

#pragma once

#include "util_time.h"

namespace Utility
{
    //--------------------------------------------------------------------------
    /** The performance timer itself */
    class CPerfTimer
    {
    public:
        /** Constructor */
        CPerfTimer()
        {
            m_pszTimerName = "NO NAME";
            m_bTimerState = TIMER_STATE_INVALID;
        }
        
        /**
         * Constructor with timer start
         * @param pszTimerName The name of the timer for print outs
         * @param startTimer True if the timer should start
         */
        CPerfTimer(const char *pszTimerName, bool startTimer = false)
        {
            m_pszTimerName = pszTimerName;
            if(startTimer)
            {
                m_ui64StartTime = mach_absolute_time();
                m_bTimerState = TIMER_STATE_STARTED;
            }
            else
            {
                m_bTimerState = TIMER_STATE_INVALID;
            }
        }
        
        /**
         * Starts the timer
         */
        void StartTimer(void)
        {
            m_ui64StartTime = mach_absolute_time();
            m_bTimerState = TIMER_STATE_STARTED;
        }
        
        /**
         * Stops the timer and returns the time in cycles
         * Use ConvertToSeconds function if you need seconds.
         */
        uint64_t StopTimer(void)
        {
            ASSERTION(m_bTimerState != TIMER_STATE_INVALID,
                      "Called StopTimer on a non-initialized performance timer!");
            
            if(m_bTimerState == TIMER_STATE_STARTED)
            {
                // Get the end time
                m_ui64EndTime = mach_absolute_time();
                m_bTimerState = TIMER_STATE_ENDED;
            }
            
            return m_ui64EndTime - m_ui64StartTime;
        }
        
        /** Gets the name of the timer */
        const char *GetTimerName(void) const
        {
            return m_pszTimerName;
        }
        
        /** Prints the timer to the standard out */
        void PrintTimer(void)
        {
            printf("%s took %f seconds to complete.\n",
                   m_pszTimerName,
                   ConvertToSeconds(StopTimer()));
        }
        
    private:
        
        /** The name of the timer */
        const char *m_pszTimerName;
        
        /** The time when the timer was started */
        uint64_t            m_ui64StartTime;
        
        /** The time when the timer ended */
        uint64_t            m_ui64EndTime;
        
        /** The state of the timer @see TIMER_STATES_E */
        TIMER_STATES_E      m_bTimerState;
    };
}

#endif // UTIL_PERF_TIMER_H
