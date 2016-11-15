#ifndef SCARAB_PARSER_HH_
#define SCARAB_PARSER_HH_

#include "param.hh"

#include <string>

namespace scarab
{

    class parser : public param_node
    {
        public:
            parser( int an_argc, char** an_argv );
            virtual ~parser();

            void parse( int an_argc, char** an_argv );
    };

} /* namespace scarab */

#endif /* SCARAB_PARSER_HH_ */
