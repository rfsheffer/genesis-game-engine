//
//  util_time.cpp
//  A class used for telling application time
//
//  Created by Ryan Sheffer on 2012-11-17.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "util_time.h"

// Invisible to program function call for setting up the performance timer conversion
// from cycles to second and back.
static double cyclesToSecondsFrac = 0.0;
void _SetupCyclesToSeconds(void)
{
    mach_timebase_info_data_t info;
    kern_return_t err = mach_timebase_info( &info );
    
    //Convert the timebase into seconds
    if(err == 0)
    {
        cyclesToSecondsFrac = 1e-9 * (double) info.numer / (double) info.denom;
    }
}

//===================================================================
// Purpose: Constructor
//===================================================================
CTime::CTime()
{
	m_ui64StartTime = 0;
    m_ui64CurTime = 0;
	m_ui64AccumTime = 0;
	m_ui64LastAccumTime = 0;
	m_ui64ElapsedTime = 0;

	m_bPerformance_Timer = FALSE;
}

//===================================================================
// Purpose: Initialize Timers
//===================================================================
void CTime::Init()
{
	// Start the timers!
#if defined(_WIN)

	LARGE_INTEGER freq;

	if ( QueryPerformanceFrequency( &freq ) )
	{
		m_bPerformance_Timer = TRUE;

		m_dPerfFrequency = double(freq.QuadPart)/100.0;

		// Get Performance Time
		QueryPerformanceCounter( &freq );
		m_i64PerfStartTime = freq.QuadPart;
		m_i64PerfElapsedTime = m_i64PerfStartTime;
	}

#elif defined(_MAC)

	m_bPerformance_Timer = TRUE;
    
    m_ui64StartTime = mach_absolute_time();
    
    // Start the timer off with an accumulation time
    m_ui64AccumTime = 0;
    m_ui64LastAccumTime = m_ui64StartTime;
    m_ui64ElapsedTime = 0;

#endif
}

//===================================================================
// Purpose: Update Timers
//===================================================================
void CTime::Update()
{
#if defined(_WIN)

	if( m_bPerformance_Timer )
	{
		QueryPerformanceCounter( (LARGE_INTEGER *)&m_i64PerfCurTime );
		m_dElapsedTime = ( ( m_i64PerfCurTime - m_i64PerfElapsedTime ) / m_dPerfFrequency );
		m_i64PerfElapsedTime = m_i64PerfCurTime;
	}

#elif defined(_MAC)
    
    // Set the current time
    m_ui64CurTime = mach_absolute_time();
    
    // Set the elapsed time
    m_ui64ElapsedTime = m_ui64CurTime - m_ui64LastAccumTime;
    
    // Add the elapsed time to the accumulation
    m_ui64AccumTime += m_ui64ElapsedTime;
    
    // Set the last time to now
    m_ui64LastAccumTime = m_ui64CurTime;

#endif
}

//===================================================================
// Purpose: This uses the mach timer CPU frequency to convert the CPU
// number of cycles to nano-seconds, then we convert that to seconds.
// NOTE: This is a useful function for getting a time for debug messages,
// however, when dealing with time sensitive code, the programmer shouldn't
// reply on (as accurate as it can be) floating point math.
//===================================================================
double ConvertToSeconds(uint64_t perfTime)
{
    if(cyclesToSecondsFrac == 0.0)
    {
        _SetupCyclesToSeconds();
    }
    
    return cyclesToSecondsFrac * perfTime;
}

//===================================================================
// Purpose: Converts a time in seconds to a performance time
//===================================================================
uint64_t ConvertToCycles(double time)
{
    if(cyclesToSecondsFrac == 0.0)
    {
        _SetupCyclesToSeconds();
    }
    
    return uint64_t(time / cyclesToSecondsFrac);
}