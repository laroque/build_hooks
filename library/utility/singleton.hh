#ifndef SCARAB_SINGLETON_HH_
#define SCARAB_SINGLETON_HH_

#include "destroyer.hh"
#include "mutex.hh"

#include <cstddef>

namespace scarab
{

#define allow_singleton_access( class_name ) \
    friend class scarab::singleton< class_name >; \
    friend class scarab::destroyer< class_name >;

    template< class XType >
    class singleton
    {
        public:
            static XType* get_instance();
            static void kill_instance();

        private:
            static void create_instance();
            static void delete_instance();

        private:
            static XType* f_instance;
            static destroyer< XType > f_destroyer;
            static mutex f_mutex;

        protected:
            singleton();

            friend class destroyer< XType >;
            ~singleton();
    };

    template< class XType >
    XType* singleton< XType >::f_instance = NULL;

    template< class XType >
    destroyer< XType > singleton< XType >::f_destroyer;

    template< class XType >
    mutex singleton< XType >::f_mutex;

    template< class XType >
    XType* singleton< XType >::get_instance()
    {
        if( f_instance == NULL )
        {
            f_mutex.lock();
            create_instance();
            f_mutex.unlock();
        }
        return f_instance;
    }

    template< class XType >
    void singleton< XType >::kill_instance()
    {
        if( f_instance != NULL )
        {
            f_mutex.lock();
            delete_instance();
            f_mutex.unlock();
        }
        return;
    }

    template< class XType >
    void singleton< XType >::create_instance()
    {
        if( f_instance == NULL )
        {
            f_instance = new XType();
            f_destroyer.set_doomed( f_instance );
        }
    }

    template< class XType >
    void singleton< XType >::delete_instance()
    {
        if( f_instance != NULL )
        {
            delete f_instance;
            f_instance = NULL;
            f_destroyer.set_doomed( NULL );
        }
    }

    template< class XType >
    singleton< XType >::singleton()
    {
    }
    template< class XType >
    singleton< XType >::~singleton()
    {
    }

} /* namespace scarab */

#endif /* SCARAB_SINGLETON_HH_ */
