/*
 * typename.cc
 *
 *  Created on: Feb 10, 2016
 *      Author: nsoblath
 */

#include "typename.hh"

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
#endif


namespace scarab
{

#ifdef __GNUG__
#ifdef USE_CPP11

    std::string demangle( const char* a_name )
    {

        int t_status = -4; // some arbitrary value to eliminate the compiler warning

        std::unique_ptr< char, void(*)( void* ) > res( abi::__cxa_demangle( a_name, NULL, NULL, &t_status ), std::free );

        return ( t_status==0 ) ? res.get() : a_name ;
    }

#else // USE_CPP11

    struct handle
    {
        char* f_ptr;
        handle( char* a_ptr ) : f_ptr( a_ptr ) {}
        ~handle() { std::free( f_ptr ); }
    };


    std::string demangle( const char* a_name )
    {

        int t_status = -4; // some arbitrary value to eliminate the compiler warning

        handle result( abi::__cxa_demangle( a_name, NULL, NULL, &t_status ) );

        return ( t_status==0 ) ? result.f_ptr : a_name ;
    }

#endif // USE_CPP11

#else // __GNUG__

    // does nothing if not g++
    std::string demangle( const char* a_name ) {
        return a_name;
    }

#endif // __GNUG__

}
