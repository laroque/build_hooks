/*
 * param_json.cc
 *
 *  Created on: March 27, 2015
 *      Author: nsoblath, bhlaroque
 */

#define SCARAB_API_EXPORTS

#include <sstream>
using std::string;
using std::stringstream;

#include "param_json.hh"

#include "logger.hh"


namespace scarab
{
    LOGGER( dlog, "param" );

    REGISTER_PARAM_INPUT_CODEC( param_input_json, "json" );

    param_input_json::param_input_json()
    {
    }
    param_input_json::~param_input_json()
    {
    }

    param* param_input_json::read_file( const std::string& a_filename, const param_node* )
    {
        FILE* t_config_file = fopen( a_filename.c_str(), "r" );
        if( t_config_file == NULL )
        {
            LERROR( dlog, "file <" << a_filename << "> did not open" );
            return NULL;
        }
        rapidjson::FileStream t_file_stream( t_config_file );

        rapidjson::Document t_config_doc;
        if( t_config_doc.ParseStream<0>( t_file_stream ).HasParseError() )
        {
            unsigned errorPos = t_config_doc.GetErrorOffset();
            rewind( t_config_file );
            unsigned iChar, newlineCount = 1, lastNewlinePos = 0;
            int thisChar;
            for( iChar = 0; iChar != errorPos; ++iChar )
            {
                thisChar = fgetc( t_config_file );
                if( thisChar == EOF )
                {
                    break;
                }
                if( thisChar == '\n' || thisChar == '\r' )
                {
                    newlineCount++;
                    lastNewlinePos = iChar + 1;
                }
            }
            if( iChar == errorPos )
            {
                LERROR( dlog, "error parsing config file :\n" <<
                        '\t' << t_config_doc.GetParseError() << '\n' <<
                        "\tThe error was reported at line " << newlineCount << ", character " << errorPos - lastNewlinePos );
            }
            else
            {
                LERROR( dlog, "error parsing config file :\n" <<
                        '\t' << t_config_doc.GetParseError() <<
                        "\tend of file reached before error location was found" );
            }
            fclose( t_config_file );
            return NULL;
        }
        fclose( t_config_file );

        return param_input_json::read_document( t_config_doc );
    }

    param* param_input_json::read_string( const std::string& a_json_string, const param_node* )
    {
        rapidjson::Document t_config_doc;
        if( t_config_doc.Parse<0>( a_json_string.c_str() ).HasParseError() )
        {
            LERROR( dlog, "error parsing string:\n" << t_config_doc.GetParseError() );
            return NULL;
        }
        return param_input_json::read_document( t_config_doc );
    }

    param_node* param_input_json::read_document( const rapidjson::Document& a_doc )
    {
        param_node* t_config = new param_node();
        for( rapidjson::Value::ConstMemberIterator jsonIt = a_doc.MemberBegin();
                jsonIt != a_doc.MemberEnd();
                ++jsonIt)
        {
            t_config->replace( jsonIt->name.GetString(), param_input_json::read_value( jsonIt->value ) );
        }
        return t_config;
    }

    param* param_input_json::read_value( const rapidjson::Value& a_value )
    {
        if( a_value.IsNull() )
        {
            return new param();
        }
        if( a_value.IsObject() )
        {
            param_node* t_config_object = new param_node();
            for( rapidjson::Value::ConstMemberIterator jsonIt = a_value.MemberBegin();
                    jsonIt != a_value.MemberEnd();
                    ++jsonIt)
            {
                t_config_object->replace( jsonIt->name.GetString(), param_input_json::read_value( jsonIt->value ) );
            }
            return t_config_object;
        }
        if( a_value.IsArray() )
        {
            param_array* t_config_array = new param_array();
            for( rapidjson::Value::ConstValueIterator jsonIt = a_value.Begin();
                    jsonIt != a_value.End();
                    ++jsonIt)
            {
                t_config_array->push_back( param_input_json::read_value( *jsonIt ) );
            }
            return t_config_array;
        }
        if( a_value.IsString() )
        {
            //LWARN( dlog, "reading string from json: " << a_value.GetString() );
            return new param_value( a_value.GetString() );
        }
        if( a_value.IsBool() )
        {
            //LWARN( dlog, "reading bool from json: " << a_value.GetBool() );
            return new param_value( a_value.GetBool() );
        }
        if( a_value.IsInt() )
        {
            //LWARN( dlog, "reading int from json: " << a_value.GetInt() );
            return new param_value( a_value.GetInt() );
        }
        if( a_value.IsUint() )
        {
            //LWARN( dlog, "reading uint from json: " << a_value.GetUint() );
            return new param_value( a_value.GetUint() );
        }
        if( a_value.IsInt64() )
        {
            //LWARN( dlog, "reading int64 from json: " << a_value.GetInt64() );
            return new param_value( a_value.GetInt64() );
        }
        if( a_value.IsUint64() )
        {
            //LWARN( dlog, "reading uint64 from json: " << a_value.GetUint64() );
            return new param_value( a_value.GetUint64() );
        }
        if( a_value.IsDouble() )
        {
            //LWARN( dlog, "reading double from json: " << a_value.GetDouble() );
            return new param_value( a_value.GetDouble() );
        }
        LWARN( dlog, "(config_reader_json) unknown type; returning null value" );
        return new param();
    }


    REGISTER_PARAM_OUTPUT_CODEC( param_output_json, "json" );

    param_output_json::param_output_json()
    {}

    param_output_json::~param_output_json()
    {}

    bool param_output_json::write_file( const param& a_to_write, const std::string& a_filename, const param_node* a_options )
    {
        if( a_filename.empty() )
        {
            LERROR( dlog, "Filename cannot be an empty string" );
            return false;
        }

        FILE* file = fopen( a_filename.c_str(), "w" );
        if( file == NULL )
        {
            LERROR( dlog, "Unable to open file: " << a_filename );
            return false;
        }

        rapidjson::FileStream t_filestream( file );

        json_writing_style t_style = k_compact;
        if( a_options->has( "style" ) )
        {
            if( a_options->value_at( "style" )->is_uint() )
            {
                t_style = (json_writing_style)a_options->get_value< unsigned >( "style", k_compact );
            }
            else
            {
                string t_style_string( a_options->get_value( "style", "compact" ) );
                if( t_style_string == string( "pretty" ) ) t_style = k_pretty;
            }
        }

        bool t_result = false;
        if( t_style == k_compact )
        {
            rj_file_writer t_writer( t_filestream );
            t_result = param_output_json::write_param( a_to_write, &t_writer );
        }
        else
        {
            rj_pretty_file_writer t_writer( t_filestream );
            t_result = param_output_json::write_param( a_to_write, &t_writer );
        }

        if (! t_result )
        {
            LERROR( dlog, "Error while writing file" );
            return false;
        }

        return true;
    }

    bool param_output_json::write_string( const param& a_to_write, std::string& a_string, const param_node* a_options )
    {
        rapidjson::StringBuffer t_str_buff;

        json_writing_style t_style = k_compact;
        if( a_options->has( "style" ) )
        {
            if( a_options->value_at( "style" )->is_uint() )
            {
                t_style = (json_writing_style)a_options->get_value< unsigned >( "style", k_compact );
            }
            else
            {
                string t_style_string( a_options->get_value( "style", "compact" ) );
                if( t_style_string == string( "pretty" ) ) t_style = k_pretty;
            }
        }

        bool t_result = false;
        if( t_style == k_compact )
        {
            rj_string_writer t_writer( t_str_buff );
            t_result = param_output_json::write_param( a_to_write, &t_writer );
        }
        else
        {
            rj_pretty_string_writer t_writer( t_str_buff );
            t_result = param_output_json::write_param( a_to_write, &t_writer );
        }

        if (! t_result )
        {
            LERROR( dlog, "Error while writing string" );
            return false;
        }

        a_string.assign( t_str_buff.GetString() );

        return true;
    }

} /* namespace scarab */
