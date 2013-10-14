// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    20.07.2013 11:27:07 EDT
// File:    max_module.hpp

#ifndef __MAX_MODULE_HEADER
#define __MAX_MODULE_HEADER

#include "module.hpp"

namespace ustd {
    namespace detail {
        template<>
        struct requirement<tag::max> {
            typedef list_end type;
        };
    }//end namespace detail
    
    template<typename T, typename _base>
    class module<T, tag::max, _base>: public _base {
        typedef _base base;
        T const init_max = T();
    public:
        //------------------- ctor -------------------
        module(): base(), max_(init_max) {
        }
        //------------------- ops -------------------
        void operator<<(T const & in) {
            base::operator<<(in);
            if(in > max_)
                max_ = in;
        }
        //------------------- fct -------------------
        T const & max() {
            return max_;
        }
        void clear() {
            base::clear();
            max_ = init_max;
        }
    private:
        T max_;
    };
}//end namespace ustd 

#endif //__MAX_MODULE_HEADER
