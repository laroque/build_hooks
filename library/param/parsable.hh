#ifndef SCARAB_PARSABLE_HH_
#define SCARAB_PARSABLE_HH_

#include "scarab_api.hh"

#include "param.hh"

#include <string>

namespace scarab
{
    class SCARAB_API parsable : public param_node
    {
        public:
            parsable();
            parsable( const std::string& a_addr_with_value );
            parsable( const std::string& a_addr, const std::string& a_value );
            parsable( const parsable& a_orig );
            ~parsable();

        private:
            void add_next( param_node* a_parent, const std::string& a_addr, const std::string& a_value );

        public:
            static const char f_value_separator = '=';
            static const char f_node_separator = '.';
    };

} /* namespace scarab */

#endif /* SCARAB_PARSABLE_HH_ */
