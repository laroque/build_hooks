/*
 * lock.hh
 *
 *  Created on: Feb 9, 2016
 *      Author: nsoblath
 */

#ifndef SCARAB_LIBRARY_UTILITY_LOCK_HH_
#define SCARAB_LIBRARY_UTILITY_LOCK_HH_

namespace scarab
{
    class mutex;

    class lock_guard
    {
        public:
            lock_guard( mutex& a_mutex );
            virtual ~lock_guard();

            void lock();
            void unlock();

            bool try_lock();

        private:
            mutex* f_mutex_ptr;
    };

} /* namespace scarab */

#endif /* SCARAB_LIBRARY_UTILITY_LOCK_HH_ */
