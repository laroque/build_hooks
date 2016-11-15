/*
 * scarab_api.hh
 *
 *  Created on: Jan 1, 2016
 *      Author: nsoblath
 */

#ifndef SCARAB_API_HH_
#define SCARAB_API_HH_


namespace scarab
{
    // API export macros for windows
#ifdef _WIN32
#  ifdef SCARAB_API_EXPORTS
#    define SCARAB_API __declspec(dllexport)
#    define SCARAB_EXPIMP_TEMPLATE
#  else
#    define SCARAB_API __declspec(dllimport)
#    define SCARAB_EXPIMP_TEMPLATE extern
#  endif
#else
#  define SCARAB_API
#endif

}

#endif /* SCARAB_API_HH_ */
