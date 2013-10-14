// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    12.06.2013 19:36:38 EDT
// File:    reset.hpp

#ifndef __RESET_HEADER
#define __RESET_HEADER

namespace util {
    void reset() {
        asm volatile ("  jmp 0");
    }
}//end namespace util

#endif //__RESET_HEADER
