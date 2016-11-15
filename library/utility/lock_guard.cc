/*
 * lock.cc
 *
 *  Created on: Feb 9, 2016
 *      Author: nsoblath
 */

#include "lock_guard.hh"

#include "mutex.hh"


namespace scarab
{

    lock_guard::lock_guard( mutex& a_mutex ) :
            f_mutex_ptr( &a_mutex )
    {
        f_mutex_ptr->lock();
    }

    lock_guard::~lock_guard()
    {
        f_mutex_ptr->unlock();
    }

    void lock_guard::lock()
    {
        f_mutex_ptr->lock();
        return;
    }

    void lock_guard::unlock()
    {
        f_mutex_ptr->unlock();
        return;
    }

    bool lock_guard::try_lock()
    {
        return f_mutex_ptr->trylock();
    }


} /* namespace scarab */
