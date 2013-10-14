// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    20.07.2013 11:27:09 EDT
// File:    error_module.hpp

#ifndef __ERROR_MODULE_HEADER
#define __ERROR_MODULE_HEADER

#ifndef Arduino_h
    #include <cmath>
#endif

#include "module.hpp"

namespace ustd {
    namespace detail {
        template<>
        struct requirement<tag::error> {
            typedef typename make_list<tag::count, tag::mean>::type type;
        };
    }//end namespace detail
    
    template<typename T, typename _base>
    class module<T, tag::error, _base>: public _base {
        typedef _base base;
        typedef typename mean_trait<T>::type error_type;
    public:
        //------------------- ctor -------------------
        module(): base(), sum2_(0) {
        }
        //------------------- ops -------------------
        void operator<<(T const & in) {
            base::operator<<(in);
            sum2_ += error_type(in) * in;
        }//------------------- fct -------------------
        error_type std() const {
            //~ using std::sqrt;
            return sqrt((sum2_ - base::mean() * base::mean() * base::count()) / (base::count() - 1));
        }
        error_type m_std() const {
            //~ using std::sqrt;
            return std() / sqrt(base::count());
        }
        void clear() {
            base::clear();
            sum2_ = error_type();
        }
    private:
        error_type sum2_;
    };
}//end namespace ustd 

#endif //__ERROR_MODULE_HEADER
