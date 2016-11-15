/*
 * path.cc
 *
 *  Created on: Jan 22, 2016
 *      Author: nsoblath
 */

#define SCARAB_API_EXPORTS

#include "path.hh"

using std::string;
using boost::filesystem::canonical;

namespace scarab
{
    path SCARAB_API expand_path( const string& a_path )
    {
        string t_exp_path( a_path );
#ifndef _WIN32
        // POSIX-shell-like expansion
        wordexp_t t_expansion_result;
        wordexp( a_path.c_str(), &t_expansion_result, 0 );
        if( t_expansion_result.we_wordc > 0 )
        {
            t_exp_path = string( t_expansion_result.we_wordv[0] );
        }
        wordfree( &t_expansion_result );
#endif
        // do canonical expansion; return the absolute path
        return canonical( path( t_exp_path ) );
    }

}
