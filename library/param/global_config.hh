/*
 * global_config.hh
 *
 *  Created on: Aug 25, 2016
 *      Author: nsoblath
 */

#ifndef SCARAB_GLOBAL_CONFIG_HH_
#define SCARAB_GLOBAL_CONFIG_HH_

#include "param.hh"
#include "singleton.hh"

namespace scarab
{

    class global_config : public singleton< global_config >
    {
        public:
            void set_config( const param_node& a_config );

            const param_node& retrieve() const;

        private:
            param_node f_config;

        protected:
            friend class scarab::singleton< global_config >;
            friend class scarab::destroyer< global_config >;
            global_config();
            ~global_config();

    };

} /* namespace scarab */

#endif /* MIDGE_SCARAB_LIBRARY_PARAM_GLOBAL_CONFIG_HH_ */
