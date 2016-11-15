/*
 * cancelable.cc
 *
 *  Created on: Jan 24, 2016
 *      Author: nsoblath
 */

#include "cancelable.hh"

namespace scarab
{

    cancelable::cancelable() :
            f_canceled( false )
    {
    }

    cancelable::~cancelable()
    {
    }

    void cancelable::do_cancellation()
    {
        // override in derived class
        return;
    }

    void cancelable::do_reset_cancellation()
    {
        // override in derived class
        return;
    }

} /* namespace scarab */
