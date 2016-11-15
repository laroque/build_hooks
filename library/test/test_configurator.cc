/*
 * test_configurator.cc
 *
 *  Created on: Feb 27, 2014
 *      Author: nsoblath
 *
 *  Command-line arguments: any standard scarab-compliant arguments, e.g.:
 *    - config=[config file]
 *    - key=value
 *    - json="[json]"
 */

#include "configurator.hh"
#include "logger.hh"

using namespace scarab;
using namespace std;

LOGGER( conflog, "test_configurator" );

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        LERROR( conflog, "Please provide some command-line arguments." );
        return -1;
    }

    configurator t_configurator( argc, argv );

    LINFO( conflog, "Final configuration:\n" << t_configurator.config() );

    return 0;
}
