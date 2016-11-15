/*
 * path.hh
 *
 *  Created on: Jan 22, 2016
 *      Author: nsoblath
 */

#ifndef SCARAB_PATH_HH_
#define SCARAB_PATH_HH_

#include "scarab_api.hh"

#include <boost/filesystem.hpp>

#include <string>

#ifndef _WIN32
#include <wordexp.h>
#endif

namespace scarab
{
    typedef boost::filesystem::path path;

    path SCARAB_API expand_path( const std::string& a_path );

}



#endif /* SCARAB_PATH_HH_ */
