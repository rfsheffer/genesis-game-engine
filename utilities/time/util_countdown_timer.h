//
//  util_stopwatch.h
//	A class for counting down
//
//  Created by Ryan Sheffer on 2012-11-17.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_COUNTDOWN_TIMER_H
#define UTIL_COUNTDOWN_TIMER_H

#include "util_time.h"

namespace Time
{
	class CCountdownTimer
	{
	public:

		/** Constructor */
		CCountdownTimer() : m_ui64EndTime(0), m_ui64Duration(0)
		{
			
		}

		inline void Reset( void )
		{
			m_ui64EndTime = CSystemTime::GetSystemTicks() + m_ui64Duration;
		}	

		inline void Start(double duration)
		{
			m_ui64Duration = SecondsToTicks(duration);
			m_ui64EndTime = CSystemTime::GetSystemTicks() + m_ui64Duration;
		}

		inline void StartFromTime(double startTime, double duration)
		{
			m_ui64Duration = SecondsToTicks(duration);
			m_ui64EndTime = SecondsToTicks(startTime) + m_ui64Duration;
		}

		inline void Invalidate( void )
		{
			// The likelihood of a valid time being 0 is nearly impossible.
			m_ui64EndTime = 0;
		}		

		inline bool HasStarted( void ) const
		{
			return (m_ui64EndTime > 0);
		}

		inline bool IsElapsed( void ) const
		{
			return (CSystemTime::GetSystemTicks() > m_ui64EndTime);
		}

		inline double GetElapsedTime( void ) const
		{
			return TicksToSeconds(CSystemTime::GetSystemTicks() - (m_ui64EndTime - m_ui64Duration));
		}

		inline double GetRemainingTime( void ) const
		{
			return TicksToSeconds(m_ui64EndTime - CSystemTime::GetSystemTicks());
		}

		inline double GetCountdownDuration( void ) const
		{
			return (m_ui64EndTime > 0) ? TicksToSeconds(m_ui64Duration) : 0.0f;
		}

	private:

		uint64_t	m_ui64Duration;
		uint64_t	m_ui64EndTime;
	};
}

#endif // UTIL_COUNTDOWN_TIMER_H