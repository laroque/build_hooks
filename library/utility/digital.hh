/*
 * digital.h
 *
 * written by jared kofron <jared.kofron@gmail.com>
 *
 * functions for converting from D2A and A2D.  prototypes are declared in
 * digital.h.  versions are included for both floats and doubles.  there are
 * two styles of the functions inspired by the GSL way of doing things - a 
 * normal version which returns the simple type of interest, and an 'error' 
 * version which can return information about bad arguments.
 */

#ifndef SCARAB_DIGITAL_HH_
#define SCARAB_DIGITAL_HH_

#include "scarab_api.hh"

namespace scarab
{

    struct SCARAB_API dig_calib_params
    {
        unsigned bit_depth;
        unsigned levels;
        unsigned data_type_size;
        double v_range;
        double v_offset;
        double inv_levels;
        double inv_v_range;
        double dac_gain;
        bool bits_right_aligned;
    };



    SCARAB_API void get_calib_params( unsigned n_bits, unsigned data_type_size, double v_offset, double v_range, bool bits_r_aligned, dig_calib_params *params );
    SCARAB_API void get_calib_params2( unsigned n_bits, unsigned data_type_size, double v_offset, double v_range, double dac_gain, bool bits_r_aligned, dig_calib_params *params );


    /*
     * convert a digital <=64 bit value to a double or float.
     */
    template< typename dig_type, typename an_type >
    an_type d2a( dig_type dig, const struct dig_calib_params* params )
    {
        return params->v_offset + params->dac_gain * ( an_type )dig;
    }

    /*
     * convert an analog value to a digital value.
     */
    template< typename an_type, typename dig_type >
    dig_type a2d( an_type analog, const struct dig_calib_params* params )
    {
        analog = ( analog - params->v_offset ) * params->inv_v_range * (an_type)(params->levels);
        if( analog > (an_type)(params->levels - 1) ) analog = params->levels - 1;
        else if( analog < 0. ) analog = 0.;
        return (dig_type)analog;
    }

}

#endif // SCARAB_DIGITAL_HH_
