/*
 * test_logger.cc
 *
 *  Created on: Jan 4, 2016
 *      Author: nsoblath
 */

#include "logger.hh"

using namespace scarab;

LOGGER( tlog, "test_logger" );

int main()
{
    LDEBUG( tlog, "This is a DEBUG message" );
    LINFO( tlog, "This is an LINFO( message" );
    LWARN( tlog, "This is a WARN message" );
    LERROR( tlog, "This is an ERROR message" );

    return 0;
}


