
#define SCARAB_API_EXPORTS

#include "mutex.hh"

namespace scarab
{
#ifndef USE_CPP11

    mutex::mutex()
    {
        pthread_mutex_init( &f_mutex, NULL );
    }
    mutex::~mutex()
    {
        pthread_mutex_destroy( &f_mutex );
    }

    bool mutex::trylock()
    {
        if( pthread_mutex_trylock( &f_mutex ) == 0 )
        {
            return true;
        }
        return false;
    }

    void mutex::lock()
    {
        pthread_mutex_lock( &f_mutex );
        return;
    }
    void mutex::unlock()
    {
        pthread_mutex_unlock( &f_mutex );
        return;
    }

#else /* USE_CPP11 */

    mutex::mutex()
    {
    }
    mutex::~mutex()
    {
    }

    bool mutex::trylock()
    {
        return f_mutex.try_lock();
    }

    void mutex::lock()
    {
        f_mutex.lock();
        return;
    }
    void mutex::unlock()
    {
        f_mutex.unlock();
        return;
    }

#endif /* _WIN32 */
}
