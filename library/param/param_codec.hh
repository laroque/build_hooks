/*
 * param_codec.hh
 *
 *  Created on: Aug 10, 2016
 *      Author: obla999
 */

#ifndef SCARAB_PARAM_CODEC_HH_
#define SCARAB_PARAM_CODEC_HH_

#include "scarab_api.hh"

#include "factory.hh"

#include <string>

namespace scarab
{
    class param;
    class param_node;

#define REGISTER_PARAM_INPUT_CODEC(codec_class, encoding) \
        static registrar< param_input_codec, codec_class > s_param_input_codec##codec_class##_registrar( encoding );

    class SCARAB_API param_input_codec
    {
        public:
            param_input_codec();
            virtual ~param_input_codec();

            virtual param* read_file( const std::string& a_filename, const param_node* a_options = nullptr ) = 0;
            virtual param* read_string( const std::string& a_string, const param_node* a_options = nullptr ) = 0;
    };


    class SCARAB_API param_output_codec
    {
        public:
            param_output_codec();
            virtual ~param_output_codec();

            virtual bool write_file( const param& a_param, const std::string& a_filename, const param_node* a_options = nullptr ) = 0;
            virtual bool write_string( const param& a_param, std::string& a_string, const param_node* a_options = nullptr ) = 0;
    };

#define REGISTER_PARAM_OUTPUT_CODEC(codec_class, encoding) \
        static registrar< param_output_codec, codec_class > s_param_output_codec##codec_class##_registrar( encoding );


    class SCARAB_API param_translator
    {
        public:
            param_translator();
            ~param_translator();

        public:
            param* read_file( const std::string& a_filename, const param_node* a_options = nullptr  );
            param* read_string( const std::string& a_string, const param_node* a_options = nullptr  );

        public:
            bool write_file( const param& a_param, const std::string& a_filename, const param_node* a_options = nullptr  );
            bool write_string( const param& a_param, std::string& a_string, const param_node* a_options = nullptr  );
    };



} /* namespace scarab */

#endif /* SCARAB_PARAM_CODEC_HH_ */
