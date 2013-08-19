//
//  util_time.h
//	A class designed for getting the time from the system in ticks.
//	Used by all other timer classes for determining time.
//
//  Created by Ryan Sheffer on 2012-11-17.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_TIME_H
#define UTIL_TIME_H

#if defined(_WIN)

#pragma once
#include <mmsystem.h>
#include <stdint.h>
#pragma comment(lib,"winmm.lib")
//#include <time.h>

#elif defined(_MAC)

#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h>

#endif

namespace Time
{
    /** Timer States */
    enum TIMER_STATES_E
    {
        TIMER_STATE_INVALID,
        TIMER_STATE_STARTED,
        TIMER_STATE_ENDED
    };
    
	/** High resolution time */
    class CSystemTime
    {
    public:
        
        /** Gets the time the system has been running in ticks. */
        static inline uint64_t GetSystemTicks(void)
        {
			uint64_t ui64Ticks;
			QueryPerformanceCounter((LARGE_INTEGER *)&ui64Ticks);
            return ui64Ticks;
        }

		/** Gets the time in seconds since the system has started. */
		static inline double GetSystemTimeSeconds(void)
		{
			return (GetSystemTicks() / m_sPerformanceTimeFreq) * 1e-9;
		}

		/** Gets the time in nanoseconds since the system has started. */
		static inline double GetSystemTimeNanoseconds(void)
		{
			return GetSystemTicks() / m_sPerformanceTimeFreq;
		}

	private:

		friend void InitTime(void);
		friend double TicksToSeconds(uint64_t ticks);
		friend double TicksToNanoseconds(uint64_t ticks);
		friend uint64_t SecondsToTicks(double seconds);

		static double m_sPerformanceTimeFreq;
    };

	/**
     * Must be called before timers can be used! 
     */
	inline void InitTime(void)
	{
		ASSERTION(performanceTimeFreq == 0.0, "Performance Timers Already Initialized!");

#if defined(_MAC)
		mach_timebase_info_data_t info;
		kern_return_t err = mach_timebase_info(&info);

		// Setup the scalar to convert ticks into nanoseconds
		if(err == 0)
		{
			performanceTimeFreq = (double) info.numer / (double) info.denom;
		}
#elif defined(_WIN)
		uint64_t            ui64Freq;
		if(QueryPerformanceFrequency((LARGE_INTEGER *)&ui64Freq))
		{
			// By default to stay consistent across platforms, we will always first
			// convert to nanoseconds.
			CSystemTime::m_sPerformanceTimeFreq = double(ui64Freq) / 1000000000.0;
		}
#endif
	}
    
	//--------------------------------------------------------------------------
    /**
	 * Converts a performance timers tick count into seconds.
     */
    inline double TicksToSeconds(uint64_t ticks)
    {
        return (ticks / CSystemTime::m_sPerformanceTimeFreq) * 1e-9;
    }

	//--------------------------------------------------------------------------
    /**
	 * Converts a performance timers tick count into nanoseconds.
     */
    inline double TicksToNanoseconds(uint64_t ticks)
    {
        return ticks / CSystemTime::m_sPerformanceTimeFreq;
    }
    
    //--------------------------------------------------------------------------
    /**
     * Converts a time in seconds to CPU ticks
     */
    inline uint64_t SecondsToTicks(double seconds)
    {
		return uint64_t((seconds * 1e+9) * CSystemTime::m_sPerformanceTimeFreq);
    }

	/** Simple timer which uses an operating system supplied timer */
	class CSimpleTime
	{
	public:

		/** Gets the time in seconds since the system has started. */
		static inline double GetTimeSeconds(void)
		{
#if defined(_MAC)
			timeval curTime;
			gettimeofday(&curTime, NULL);

			return curTime.tv_sec + (curTime.tv_usec * 0.000001);
#elif defined(_WIN)
			return timeGetTime() * 0.001;
#endif
		}

		/** Gets the time in nanoseconds since the system has started. */
		static inline double GetTimeMilliseconds(void)
		{
			return GetTimeSeconds() * 1000.0;
		}
	};
}

#endif // UTIL_TIME_H