//
//  util_simple_timer.h
//  A simple low resolution timer for the timing of things which aren't super
//  quick. Use util_perf_timer for a high resolution hardware based timer.
//
//  Created by Ryan Sheffer on 2012-11-17.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_TIMER_H
#define UTIL_TIMER_H

#pragma once

#include <sys/time.h>
#include "util_time.h"

class CTimerSimple
{
public:
    CTimerSimple()
    {
        m_bTimerState = TIMER_STATE_INVALID;
    }
    
    // Starts the timer
    void StartTimer(void)
    {
        gettimeofday(&m_startTime, NULL);
        m_bTimerState = TIMER_STATE_STARTED;
    }
    
    // Stops the timer and returns the time in seconds
    double StopTimer(void)
    {
        ASSERTION(m_bTimerState != TIMER_STATE_INVALID,
                  "Called StopTimer on a non-initialized simple timer!");
        
        if(m_bTimerState == TIMER_STATE_STARTED)
        {
            // Get the end time
            gettimeofday(&m_EndTime, NULL);
            m_bTimerState = TIMER_STATE_ENDED;
        }
        
        return (m_EndTime.tv_sec - m_startTime.tv_sec) +
                ((m_EndTime.tv_usec - m_startTime.tv_usec) * 0.000001);
    }
    
private:
    
    // The time in which this timer was started
    timeval m_startTime;
    
    // The time when this timer ended
    timeval m_EndTime;
    
    TIMER_STATES_E    m_bTimerState;
};

#endif // UTIL_TIMER_H
