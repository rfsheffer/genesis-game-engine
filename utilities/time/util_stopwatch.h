//
//  util_stopwatch.h
//	A class for running a stop watch
//
//  Created by Ryan Sheffer on 2012-11-17.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_STOP_WATCH_H
#define UTIL_STOP_WATCH_H

#include "util_time.h"

namespace Time
{
	class CStopWatch
	{
	public:

		/** Constructor */
		CStopWatch()
		{
			m_ui64StartTime = m_ui64CurrentTime = 0;
			m_bTimerPaused = false;
		}

		inline void Reset(void)
		{
			m_ui64StartTime = m_ui64CurrentTime = 0;
			m_bTimerPaused = false;
		}

		/** Starts the timer */
		inline void Start(void)
		{
			if(m_bTimerPaused)
			{
				// We are un-pausing the timer, so we need to shift it forward
				// by the time we were paused to keep the timer correct.
				m_ui64StartTime += (Time::CSystemTime.GetSystemTicks() - m_ui64CurrentTime);
				m_ui64CurrentTime = Time::CSystemTime.GetSystemTicks();
			}
			else
			{
				m_ui64StartTime = m_ui64CurrentTime = Time::CSystemTime.GetSystemTicks();
			}

			m_bTimerPaused = false;
		}

		/** Pauses the timer */
		inline void Pause(void)
		{
			if(m_bTimerPaused == false)
			{
				m_ui64CurrentTime = Time::CSystemTime.GetSystemTicks();
			}

			m_bTimerPaused = true;
		}

		/** Gets the timer in seconds */
		inline double GetSeconds(void)
		{
			if(m_bTimerPaused == false)
			{
				m_ui64CurrentTime = Time::CSystemTime.GetSystemTicks();
			}
			
			return TicksToSeconds(m_ui64CurrentTime - m_ui64StartTime);
		}

		/** Gets the timer in nanoseconds */
		inline double GetNanoSeconds(void)
		{
			if(m_bTimerPaused == false)
			{
				m_ui64CurrentTime = Time::CSystemTime.GetSystemTicks();
			}

			return TicksToNanoseconds(m_ui64CurrentTime - m_ui64StartTime);
		}

	private:

		uint64_t	m_ui64StartTime;
		uint64_t	m_ui64CurrentTime;
		bool		m_bTimerPaused;
	};
}

#endif // UTIL_STOP_WATCH_H