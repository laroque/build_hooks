#ifndef SCARAB_EXCEPTION_HH_
#define SCARAB_EXCEPTION_HH_

#include <exception>
#include <sstream>
#include <string>

#include "scarab_api.hh"

namespace scarab
{

    class SCARAB_API error : public ::std::exception
    {
        public:
            error();
            error( const error& );
            ~error() throw ();

            template< class x_streamable >
            error& operator<<( x_streamable a_fragment );
            error& operator<<( const std::string& a_fragment );
            error& operator<<( const char* a_fragment );

            virtual const char* what() const throw();

        private:
            std::string f_error;
    };

    template< class x_streamable >
    error& error::operator<<( x_streamable a_fragment )
    {
        std::stringstream stream;
        stream << a_fragment;
        stream >> f_error;
        return *this;
    }

    inline error& error::operator<<( const std::string& a_fragment )
    {
        f_error += a_fragment;
        return *this;
    }

    inline error& error::operator<<( const char* a_fragment )
    {
        f_error += std::string( a_fragment );
        return *this;
    }


}

#endif /* SCARAB_EXCEPTION_HH_ */
