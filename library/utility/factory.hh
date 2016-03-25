/*
 * mt_factory.hh
 *
 *  created on: Jul 31, 2012
 *      Author: nsoblath
 */

#ifndef SCARAB_FACTORY_HH_
#define SCARAB_FACTORY_HH_

#include "singleton.hh"

#include "lock_guard.hh"
#include "logger.hh"
#include "mutex.hh"

#include <map>
#include <string>
#include <utility>

namespace scarab
{
    LOGGER( slog_fact, "factory" );

    template< class XBaseType >
    class factory;

    template< class XBaseType >
    class base_registrar
    {
        public:
            base_registrar() {}
            virtual ~base_registrar() {}

        public:
            friend class factory< XBaseType >;

        protected:
            virtual XBaseType* create() const = 0;

    };

    template< class XBaseType, class XDerivedType >
    class registrar : public base_registrar< XBaseType >
    {
        public:
            registrar(const std::string& a_class_name);
            virtual ~registrar();

        protected:
            void register_class(const std::string& a_class_name) const;

            XBaseType* create() const;

    };


    template< class XBaseType >
    class factory : public singleton< factory< XBaseType > >
    {
        public:
            typedef std::map< std::string, const base_registrar< XBaseType >* > FactoryMap;
            typedef typename FactoryMap::value_type FactoryEntry;
            typedef typename FactoryMap::iterator FactoryIt;
            typedef typename FactoryMap::const_iterator FactoryCIt;

        public:
            XBaseType* create(const std::string& a_class_name);
            XBaseType* create(const FactoryCIt& iter);

            void register_class(const std::string& a_class_name, const base_registrar< XBaseType >* base_registrar);

            FactoryCIt begin() const;
            FactoryCIt end() const;

        protected:
            FactoryMap* fMap;
            mutex f_factory_mutex;

        protected:
            friend class singleton< factory >;
            friend class destroyer< factory >;
            factory();
            ~factory();
    };

    template< class XBaseType >
    XBaseType* factory< XBaseType >::create(const FactoryCIt& iter)
    {
        lock_guard( this->f_factory_mutex );
        return iter->second->create();
    }

    template< class XBaseType >
    XBaseType* factory< XBaseType >::create(const std::string& a_class_name)
    {
        //std::cout << "this factory (" << this << ") has " << fMap->size() << " entries" << std::endl;
        //for( FactoryCIt iter = fMap->begin(); iter != fMap->end(); ++iter )
        //{
        //    std::cout << "this factory has: " << iter->first << std::endl;
        //}
        lock_guard( this->f_factory_mutex );
        FactoryCIt it = fMap->find(a_class_name);
        if (it == fMap->end())
        {
            ERROR( slog_fact, "Did not find factory for <" << a_class_name << ">." );
            return NULL;
        }

        return it->second->create();
    }

    template< class XBaseType >
    void factory< XBaseType >::register_class(const std::string& a_class_name, const base_registrar< XBaseType >* a_registrar)
    {
        lock_guard( this->f_factory_mutex );
        FactoryCIt it = fMap->find(a_class_name);
        if (it != fMap->end())
        {
            ERROR( slog_fact, "Already have factory registered for <" << a_class_name << ">." );
            return;
        }
        fMap->insert(std::pair< std::string, const base_registrar< XBaseType >* >(a_class_name, a_registrar));
        //std::cout << "registered a factory for class " << a_class_name << ", factory #" << fMap->size()-1 << " for " << this << std::endl;
    }

    template< class XBaseType >
    factory< XBaseType >::factory() :
        fMap(new FactoryMap()),
        f_factory_mutex()
    {}

    template< class XBaseType >
    factory< XBaseType >::~factory()
    {
        delete fMap;
    }

    template< class XBaseType >
    typename factory< XBaseType >::FactoryCIt factory< XBaseType >::begin() const
    {
        lock_guard( this->f_factory_mutex );
        return fMap->begin();
    }

    template< class XBaseType >
    typename factory< XBaseType >::FactoryCIt factory< XBaseType >::end() const
    {
        lock_guard( this->f_factory_mutex );
        return fMap->end();
    }






    template< class XBaseType, class XDerivedType >
    registrar< XBaseType, XDerivedType >::registrar(const std::string& a_class_name) :
            base_registrar< XBaseType >()
    {
        register_class(a_class_name);
    }

    template< class XBaseType, class XDerivedType >
    registrar< XBaseType, XDerivedType >::~registrar()
    {}

    template< class XBaseType, class XDerivedType >
    void registrar< XBaseType, XDerivedType >::register_class(const std::string& a_class_name) const
    {
        factory< XBaseType >::get_instance()->register_class(a_class_name, this);
        return;
    }

    template< class XBaseType, class XDerivedType >
    XBaseType* registrar< XBaseType, XDerivedType >::create() const
    {
        return dynamic_cast< XBaseType* >(new XDerivedType());
    }

} /* namespace scarab */
#endif /* SCARAB_FACTORY_HH_ */
