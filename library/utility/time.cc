/*
 * time.cc
 *
 *  Created on: Oct 29, 2013
 *      Author: nsoblath
 */


#define SCARAB_API_EXPORTS

#include "time.hh"

namespace scarab
{

// Combined date & time, according to the ISO 8601 standard: e.g. 2015-01-31T22:35:58Z
SCARAB_API char date_time_format[] = "%Y-%m-%dT%H:%M:%SZ";

#ifdef __MACH__
double thorax_timebase = 0.0;
time_nsec_type thorax_timestart = 0;
#endif

#ifdef _WIN32
#define CLOCK_MONOTONIC 1
#define CLOCK_PROCESS_CPUTIME_ID 2
#endif

SCARAB_API int get_time_monotonic( struct timespec* time )
{
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
    if (! thorax_timestart)
    {
        mach_timebase_info_data_t tb = { .numer = 0, .denom = 1 };
        mach_timebase_info(&tb);
        thorax_timebase = tb.numer;
        thorax_timebase /= tb.denom;
        thorax_timestart = mach_absolute_time();
    }
    double diff = (mach_absolute_time() - thorax_timestart) * thorax_timebase;
    time->tv_sec = diff * MACNANO;
    time->tv_nsec = diff - (time->tv_sec * MACGIGA);
    return 0;
#else
    return clock_gettime( CLOCK_MONOTONIC, time );
#endif
}

SCARAB_API int get_time_current( struct timespec* time )
{
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
    if (! thorax_timestart)
    {
        mach_timebase_info_data_t tb = { .numer = 0, .denom = 1 };
        mach_timebase_info(&tb);
        thorax_timebase = tb.numer;
        thorax_timebase /= tb.denom;
        thorax_timestart = mach_absolute_time();
    }
    double diff = (mach_absolute_time() - thorax_timestart) * thorax_timebase;
    time->tv_sec = diff * MACNANO;
    time->tv_nsec = diff - (time->tv_sec * MACGIGA);
    return 0;
#else
	return clock_gettime(CLOCK_PROCESS_CPUTIME_ID, time);
#endif

}

SCARAB_API time_nsec_type time_to_nsec( struct timespec time )
{
    return (long long int)time.tv_sec * (long long int)NSEC_PER_SEC + (long long int)time.tv_nsec;
}

SCARAB_API double time_to_sec( struct timespec time )
{
    return (double)time.tv_sec + (double)time.tv_nsec / (double)NSEC_PER_SEC;
}

SCARAB_API void time_diff( struct timespec start, struct timespec end, struct timespec* diff )
{
    if ((end.tv_nsec - start.tv_nsec < 0))
    {
        diff->tv_sec = end.tv_sec - start.tv_sec - 1;
        diff->tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        diff->tv_sec = end.tv_sec - start.tv_sec;
        diff->tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return;
}

SCARAB_API size_t get_time_absolute_str( char* ptr )
{
    time_t raw_time;
    struct tm* processed_time;

    time(&raw_time);
    processed_time = gmtime(&raw_time);
    return strftime(ptr, 512, date_time_format, processed_time);
}

SCARAB_API std::string get_absolute_time_string()
{
    char t_string_time[ 512 ];
    get_time_absolute_str( t_string_time );
    return std::string( t_string_time );
}


#ifdef _WIN32
SCARAB_API LARGE_INTEGER getFILETIMEoffset()
{
	SYSTEMTIME s;
	FILETIME f;
	LARGE_INTEGER t;

	s.wYear = 1970;
	s.wMonth = 1;
	s.wDay = 1;
	s.wHour = 0;
	s.wMinute = 0;
	s.wSecond = 0;
	s.wMilliseconds = 0;
	SystemTimeToFileTime(&s, &f);
	t.QuadPart = f.dwHighDateTime;
	t.QuadPart <<= 32;
	t.QuadPart |= f.dwLowDateTime;
	return (t);
}

SCARAB_API int clock_gettime( int X, struct timespec *tv )
{
	LARGE_INTEGER           t;
	FILETIME            f;
	double                  microseconds;
	static LARGE_INTEGER    offset;
	static double           frequencyToMicroseconds;
	static int              initialized = 0;
	static BOOL             usePerformanceCounter = 0;

	if (!initialized) 
	{
		LARGE_INTEGER performanceFrequency;
		initialized = 1;
		usePerformanceCounter = QueryPerformanceFrequency(&performanceFrequency);
		if (usePerformanceCounter) 
		{
			QueryPerformanceCounter(&offset);
			frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.;
		}
		else 
		{
			offset = getFILETIMEoffset();
			frequencyToMicroseconds = 10.;
		}
	}
	if (usePerformanceCounter) QueryPerformanceCounter(&t);
	else 
	{
		GetSystemTimeAsFileTime(&f);
		t.QuadPart = f.dwHighDateTime;
		t.QuadPart <<= 32;
		t.QuadPart |= f.dwLowDateTime;
	}

	t.QuadPart -= offset.QuadPart;
	microseconds = (double)t.QuadPart / frequencyToMicroseconds;
	t.QuadPart = microseconds;
	tv->tv_sec = t.QuadPart * SEC_PER_NSEC;
	tv->tv_nsec = t.QuadPart % NSEC_PER_SEC;
	return (0);
}
#endif

} /* namespace scarab */
