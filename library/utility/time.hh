#ifndef SCARAB_TIME_HH_
#define SCARAB_TIME_HH_

#include "scarab_api.hh"

#include <cstdint>
#include <string>

#ifndef _WIN32
#include <sys/time.h>
#else
#include <Windows.h>
#endif
#include <time.h>

#ifdef __MACH__
#include <mach/mach_time.h>
#endif

namespace scarab
{
    typedef uint64_t time_nsec_type; // the maximum number of nanoseconds representable by a uint64_t is equivalent to 584.6 years
}

#ifndef NSEC_PER_SEC
#define NSEC_PER_SEC 1000000000
#endif

#ifndef SEC_PER_NSEC
#define SEC_PER_NSEC 1.e-9
#endif

#ifdef __MACH__
#ifndef MACNANO
#define MACNANO (+1.0E-9)
#define MACGIGA UINT64_C(1000000000)
#endif // MACNANO
    extern double thorax_timebase;
    extern scarab::time_nsec_type thorax_timestart;
#endif // __MACH__


#ifdef _WIN32
struct timespec
{
    time_t tv_sec;
    long tv_nsec;
    //inline SCARAB_API bool operator==( const timespec& rhs ) const { return tv_nsec==rhs.tv_nsec && tv_sec==rhs.tv_sec; }
    //inline SCARAB_API bool operator<( const timespec& rhs ) const { return tv_sec != rhs.tv_sec ? tv_sec < rhs.tv_sec : tv_nsec < rhs.tv_nsec; }
};
#endif
//#else
inline SCARAB_API bool operator==( const timespec& lhs, const timespec& rhs ) { return lhs.tv_nsec==rhs.tv_nsec && lhs.tv_sec==rhs.tv_sec; }
inline SCARAB_API bool operator<( const timespec& lhs, const timespec& rhs ) { return lhs.tv_sec != rhs.tv_sec ? lhs.tv_sec < rhs.tv_sec : lhs.tv_nsec < rhs.tv_nsec; }
//#endif

namespace scarab
{
#ifdef _WIN32
    SCARAB_API LARGE_INTEGER getFILETIMEoffset();
    SCARAB_API int clock_gettime( int X, struct timespec* tv );
#endif

    extern SCARAB_API char date_time_format[];

    SCARAB_API int get_time_monotonic( struct timespec* time );

    SCARAB_API int get_time_current( struct timespec* time );

    SCARAB_API time_nsec_type time_to_nsec( struct timespec time );

    SCARAB_API double time_to_sec( struct timespec time );

    SCARAB_API void time_diff( struct timespec start, struct timespec end, struct timespec* diff );

    SCARAB_API size_t get_time_absolute_str( char* ptr );

    SCARAB_API std::string get_absolute_time_string();

} /* namespace scarab */

#endif // SCARAB_TIME_HH_
