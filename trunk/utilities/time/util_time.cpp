//
//  util_time.h
//	A class designed for getting the time from the system in ticks.
//	Used by all other timer classes for determining time.
//
//  Created by Ryan Sheffer on 2012-11-17.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "winhead.h"
#include "util_time.h"

namespace Time
{
	double CSystemTime::m_sPerformanceTimeFreq = 0.0;
}