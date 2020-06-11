// StopWatch.h
// Stopwatch class for high resolution timing.
// Code by Richard S. Wright Jr.
// March 23, 1999
// 
// This function uses the High performance counter on Win32 and
// gettimeofday on Mac OS X/Linux. gettimeofday is actually pretty
// good on the Mac (about 10ms).

/* Copyright (c) 2005-2009, Richard S. Wright Jr.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list 
of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other 
materials provided with the distribution.

Neither the name of Richard S. Wright Jr. nor the names of other contributors may be used 
to endorse or promote products derived from this software without specific prior 
written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef STOPWATCH_HEADER
#define STOPWATCH_HEADER

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif


///////////////////////////////////////////////////////////////////////////////
// Simple Stopwatch class. Use this for high resolution timing 
// purposes (or, even low resolution timings)
// Pretty self-explanitory.... 
// Reset(), or GetElapsedSeconds().
class CStopWatch
	{
	public:
		CStopWatch(void)	// Constructor
			{
			#ifdef WIN32
			QueryPerformanceFrequency(&m_CounterFrequency);
			QueryPerformanceCounter(&m_LastCount);
			#else
            gettimeofday(&m_LastCount, 0);
			#endif
			}

		// Resets timer (difference) to zero
		inline void Reset(void) 
			{
			#ifdef WIN32
			QueryPerformanceCounter(&m_LastCount);
			#else
			gettimeofday(&m_LastCount, 0);
			#endif
			}					
		
		// Get elapsed time in seconds
		float GetElapsedSeconds(void)
			{
			// Get the current count
			#ifdef WIN32
			LARGE_INTEGER lCurrent;
			QueryPerformanceCounter(&lCurrent);

			return float((lCurrent.QuadPart - m_LastCount.QuadPart) /
										double(m_CounterFrequency.QuadPart));
			#else
            timeval lcurrent;
            gettimeofday(&lcurrent, 0);
            float fSeconds = (float)(lcurrent.tv_sec - m_LastCount.tv_sec);
            float fFraction = (float)(lcurrent.tv_usec - m_LastCount.tv_usec) * 0.000001f;
            return fSeconds + fFraction;
			#endif
			}	
	
	protected:
	#ifdef WIN32
		LARGE_INTEGER m_CounterFrequency;
		LARGE_INTEGER m_LastCount;
	#else
        timeval m_LastCount;
	#endif
	};


#endif
