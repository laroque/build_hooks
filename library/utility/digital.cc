/*
 * digital.c
 *
 * written by jared kofron <jared.kofron@gmail.com>
 *
 * documented prototypes are in digital.h
 */

#define SCARAB_API_EXPORTS

#include "digital.hh"

#include <cstdio>

namespace scarab
{

    SCARAB_API void get_calib_params( unsigned n_bits, unsigned data_type_size, double v_offset, double v_range, bool bits_r_aligned, dig_calib_params *params )
    {
        params->bit_depth = n_bits;
        params->levels = 1 << n_bits;
        params->data_type_size = data_type_size;
        params->v_range = v_range;
        params->v_offset = v_offset;
        params->inv_levels = 1. / (double)params->levels;
        params->inv_v_range = 1. / params->v_range;
        params->dac_gain = params->v_range * params->inv_levels;
        params->bits_right_aligned = bits_r_aligned;
        return;
    }

    SCARAB_API void get_calib_params2( unsigned n_bits, unsigned data_type_size, double v_offset, double v_range, double dac_gain, bool bits_r_aligned, dig_calib_params *params )
    {
        params->bit_depth = n_bits;
        params->levels = 1 << n_bits;
        params->data_type_size = data_type_size;
        params->v_range = v_range;
        params->v_offset = v_offset;
        params->inv_levels = 1. / ( double )params->levels;
        params->inv_v_range = 1. / params->v_range;
        params->dac_gain = dac_gain;
        params->bits_right_aligned = bits_r_aligned;
        return;
    }

}
