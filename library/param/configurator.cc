/*
 * configurator.cc
 *
 *  Created on: Nov 5, 2013
 *      Author: nsoblath
 */

#include "configurator.hh"

#include "logger.hh"
#include "param_codec.hh"
#include "param_json.hh"
#include "parser.hh"
#include "path.hh"

#ifdef __APPLE__
#include <mach-o/dyld.h>
#elif __linux
#include <unistd.h> // for readlink
#endif

using std::string;

namespace scarab
{
    LOGGER( slog, "configurator" );

    configurator::configurator( int an_argc, char** an_argv, param_node* a_default ) :
            f_exe_name( "unknown" ),
            f_master_config( new param_node() ),
            f_help_flag( false ),
            f_version_flag( false ),
            f_param_buffer( NULL ),
            f_string_buffer()
    {
        parser t_parser( an_argc, an_argv );
        //std::cout << "options parsed" << std::endl;
        //cout << t_parser );

        // first configuration: defaults
        if ( a_default != NULL )
        {
            f_master_config->merge( *a_default );
        }

        //std::cout << "first configuration complete" << std::endl;
        //cout << f_master_config );
        //cout << t_parser );

        string t_name_exe( "executable" ); // the name used to specify the executable in parser
        string t_name_config( "config" );
        string t_name_json( "json" );

        // name of executable
        //f_exe_name = t_parser.get_value( t_name_exe, f_exe_name );
#ifdef __APPLE__
        char t_exe_buf[ 2048 ];
        uint32_t t_bufsize = sizeof( t_exe_buf );
        if( _NSGetExecutablePath( t_exe_buf, &t_bufsize ) != 0 )
#elif __linux
        const size_t t_bufsize = 2048;
        char t_exe_buf[ t_bufsize ];
        if( readlink( "/proc/self/exe", t_exe_buf, t_bufsize ) < 0 )
#endif
        {
            LWARN( slog, "Could not retrieve executable file name" );
#ifdef __APPLE__
            LWARN( slog, "Executable name buffer is too small; needs size %u\n" << t_bufsize );
#endif
        }
        f_exe_name = string( t_exe_buf );

        // second configuration: config file
        if( t_parser.has( t_name_config ) )
        {
            path t_config_filename = scarab::expand_path( t_parser.get_value( t_name_config ) );
            if( ! t_config_filename.empty() )
            {
                param_translator t_translator;
                param* t_config_from_file = t_translator.read_file( t_config_filename.native() );
                if( t_config_from_file == NULL )
                {
                    throw error() << "[configurator] error parsing config file";
                }
                if( ! t_config_from_file->is_node() )
                {
                    throw error() << "[configurator] configuration file must consist of an object/node";
                }
                f_master_config->merge( t_config_from_file->as_node() );
                delete t_config_from_file;
            }
        }

        //std::cout << "second configuration complete" << std::endl;
        //cout << f_master_config );
        //cout << t_parser );

        // third configuration: command line json
        if( t_parser.has( t_name_json ) )
        {
            string t_config_json = t_parser.get_value( t_name_json );
            if( ! t_config_json.empty() )
            {
                param_input_json t_input_json;
                param* t_config_from_json = t_input_json.read_string( t_config_json );
                if( ! t_config_from_json->is_node() )
                {
                    throw error() << "[configurator] command line json must be an object";
                }
                f_master_config->merge( t_config_from_json->as_node() );
                delete t_config_from_json;
            }
        }

        //std::cout << "third configuration complete" << std::endl;
        //cout << f_master_config );
        //cout << t_parser );

        // fourth configuration: command line arguments
        t_parser.erase( t_name_exe );
        t_parser.erase( t_name_config );
        t_parser.erase( t_name_json );

        //std::cout << "removed config and json from parsed options" << std::endl;
        //cout << t_parser );
        //LDEBUG( slog, "adding command-line parser:\n" << t_parser << *f_master_config );
        f_master_config->merge( t_parser );

        // check for help and version flags
        if( f_master_config->has( "help" ) )
        {
            f_help_flag = true;
            f_master_config->erase( "help" );
        }
        if( f_master_config->has( "version" ) )
        {
            f_version_flag = true;
            f_master_config->erase( "version" );
        }

        //std::cout << "fourth configuration complete" << std::endl;
        LINFO( slog, "Final configuration:\n" << *f_master_config );
    }

    configurator::~configurator()
    {
        delete f_master_config;
    }

} /* namespace scarab */
