
#define SCARAB_API_EXPORTS

#include "error.hh"

namespace scarab
{

    error::error() :
            ::std::exception(),
            f_error()
    {
    }

    error::error( const error& an_error ) :
            std::exception(),
            f_error( an_error.f_error )
    {
    }

    error::~error() throw ()
    {
    }

    const char* error::what() const throw ()
    {
        return f_error.c_str();
    }

}
