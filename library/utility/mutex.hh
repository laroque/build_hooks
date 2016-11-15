#ifndef SCARAB_MUTEX_HH_
#define SCARAB_MUTEX_HH_

#ifndef USE_CPP11
#include <pthread.h>
#include <cstddef>
#else
#include <mutex>
#endif

#include "scarab_api.hh"

// Require C++11 to build in Windows
#ifndef USE_CPP11
#ifdef _WIN32
#error Windows build requires C++11
#endif
#endif

namespace scarab
{
    class SCARAB_API mutex
    {
        public:
            mutex();
            virtual ~mutex();

            bool trylock();

            void lock();
            void unlock();

        private:
#ifndef USE_CPP11
            pthread_mutex_t f_mutex;
#else
            std::mutex f_mutex;
#endif
    };

}

#endif /* SCARAB_MUTEX_HH_ */
