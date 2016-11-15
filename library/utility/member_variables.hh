/*
 * member_variables.hh
 *
 *  Created on: Jan 6, 2016
 *      Author: nsoblath
 */

#ifndef SCARAB_MEMBER_VARIABLES_HH_
#define SCARAB_MEMBER_VARIABLES_HH_

/**
 * Macros for class member variables
 *
 * For "normal" variables
 * Defines [type get_my_var() const] and [void set_my_var( type )]
 * The set_ function is not available if the _noset macros are used
 *  - mv_accessible
 *  - mv_accessible_noset
 *  - mv_accessible_static
 *  - mv_accessible_static_noset
 *
 * For variables accessed by reference
 * Defines [const type& my_var() const] and [type& my_var()]
 * The non-const function is not available if the _const macros are used
 *  - mv_referrable
 *  - mv_referrable_const
 *  - mv_referrable_static
 *  - mv_referrable_static_const
 *
 * For pointer variables
 * Defines [type* get_my_var() const] and void set_my_var( type* )
 * The set_ function is not available if the _noset macros are used
 *  - mv_assignable
 *  - mv_assignable_noset
 *  - mv_assignable_static
 *  - mv_assignable_static_noset
 *
 * For atomic variables
 * Defines [type get_my_var() const] and void set_my_var( type ), both thread-safe
 * The set_ function is not available if the _noset macros are used
 *  - mv_atomic
 *  - mv_atomic_noset
 *  - mv_atomic_static
 *  - mv_atomic_static_noset
 *
 */

#include <cstddef>

#define mv_accessible_noset( x_type, x_variable )\
    public:\
        const x_type& get_##x_variable() const\
        {\
            return f_##x_variable;\
        }\
    protected:\
        x_type f_##x_variable;

#define mv_accessible( x_type, x_variable )\
    public:\
        void set_##x_variable( const x_type& p_variable )\
        {\
            f_##x_variable = p_variable;\
            return;\
        }\
        mv_accessible_noset( x_type, x_variable )

#define mv_accessible_static_noset( x_type, x_variable )\
    public:\
        static const x_type& get_##x_variable()\
        {\
            return s_##x_variable;\
        }\
    protected:\
        static x_type s_##x_variable;

#define mv_accessible_static( x_type, x_variable )\
    public:\
        static void set_##x_variable( const x_type& p_variable )\
        {\
            s_##x_variable = p_variable;\
            return;\
        }\
        mv_accessible_static_noset( x_type, x_variable )

#define mv_referrable_const( x_type, x_variable )\
    public:\
        const x_type& x_variable() const\
        {\
            return f_##x_variable;\
        }\
    protected:\
        x_type f_##x_variable;

#define mv_referrable( x_type, x_variable )\
    public:\
        x_type& x_variable()\
        {\
            return f_##x_variable;\
        }\
        mv_referrable_const( x_type, x_variable )

#define mv_referrable_static_const( x_type, x_variable )\
    public:\
        static const x_type& x_variable()\
        {\
            return s_##x_variable;\
        }\
    protected:\
        static x_type s_##x_variable;

#define mv_referrable_static( x_type, x_variable )\
    public:\
        static x_type& x_variable()\
        {\
            return s_##x_variable;\
        }\
        mv_referrable_static_const( x_type, x_variable )

#define mv_assignable_noset( x_type, x_variable )\
    public:\
        x_type* get_##x_variable() const\
        {\
            return f_##x_variable;\
        }\
    protected:\
        x_type* f_##x_variable;

#define mv_assignable( x_type, x_variable )\
    public:\
        void set_##x_variable( x_type* p_variable )\
        {\
            delete f_##x_variable;\
            f_##x_variable = p_variable;\
            return;\
        }\
        mv_assignable_noset( x_type, x_variable )

#define mv_assignable_static_noset( x_type, x_variable )\
    public:\
        static x_type* get_##x_variable()\
        {\
            return s_##x_variable;\
        }\
    protected:\
        static x_type* s_##x_variable;

#define mv_assignable_static( x_type, x_variable )\
    public:\
        static void set_##x_variable( x_type* p_variable )\
        {\
            delete s_##x_variable;\
            s_##x_variable = p_variable;\
            return;\
        }\
        mv_assignable_static_noset( x_type, x_variable )

#define mv_atomic_noset( x_type, x_variable )\
    public:\
        x_type get_##x_variable() const\
        {\
            return f_##x_variable.load();\
        }\
    protected:\
        std::atomic< x_type > f_##x_variable;

#define mv_atomic( x_type, x_variable )\
    public:\
        void set_##x_variable( x_type p_variable )\
        {\
            f_##x_variable.store( p_variable );\
            return;\
        }\
        mv_atomic_noset( x_type, x_variable )

#define mv_atomic_static_noset( x_type, x_variable )\
    public:\
        static x_type get_##x_variable()\
        {\
            return s_##x_variable.load();\
        }\
    protected:\
        static std::atomic< x_type > s_##x_variable;

#define mv_atomic_static( x_type, x_variable )\
    public:\
        static void set_##x_variable( x_type p_variable )\
        {\
            s_##x_variable.store( p_variable );\
            return;\
        }\
        mv_atomic_static_noset( x_type, x_variable )

#endif /* SCARAB_MEMBER_VARIABLES_HH_ */
