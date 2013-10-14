// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    20.07.2013 12:41:39 EDT
// File:    mean_trait.hpp

#ifndef __MEAN_TRAIT_HEADER
#define __MEAN_TRAIT_HEADER

#include "meta_template.hpp"

namespace detail {
    template<typename T>
    struct use_double_identifier {
        static T t;
        
        static char check(T);
        static double check(double);
        
        enum {value = (sizeof(check((t+t)/double(2))) == sizeof(double))};
    };

    //------------------- full specialisation -------------------
    template<>
    struct use_double_identifier<double> {
        enum {value = true}; //doesn't matter if true or false
    };
}//end namespace detail

//------------------- mean_trait -------------------
template<typename T>
struct mean_trait {
    typedef 
        typename 
            m_if<detail::use_double_identifier<T>::value
                  , double
                  , T
        >::type
    type;
};

#endif //__MEAN_TRAIT_HEADER
