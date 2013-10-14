// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    20.07.2013 12:09:08 EDT
// File:    module.hpp

#ifndef __MODULE_HEADER
#define __MODULE_HEADER

#include "tags.hpp"
#include "../../util/meta_list.hpp"

namespace ustd {
    namespace detail {
        template<typename T>
        struct requirement {
            typedef list_end type;
        };
    }//end namespace detail
    
    template<typename T>
    struct accumulator_base {
        void operator<<(T const & in) {
        }
        void clear() {
        }
    };
    template<typename T, typename mod, typename _base>
    class module {
    };
}//end namespace ustd

#endif //__MODULE_HEADER
