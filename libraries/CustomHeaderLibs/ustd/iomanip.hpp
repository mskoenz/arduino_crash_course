// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    08.06.2013 12:17:31 EDT
// File:    iomanip.hpp

#ifndef __IOMANIP_HEADER
#define __IOMANIP_HEADER

namespace ustd {
    
    #define BUILD_FCT(NAME, TYPE) \
    struct NAME { \
        typedef TYPE NAME ## _type; \
        NAME(NAME ## _type const & data): data_(data) { \
        } \
        NAME ## _type const & operator()() const { \
            return data_; \
        } \
        NAME ## _type data_; \
    };
    
    BUILD_FCT(setw, uint8_t)
    BUILD_FCT(setfill, char)
    BUILD_FCT(setprecision, uint8_t)
    BUILD_FCT(setbase, uint8_t)
    
    #undef BUILD_FCT
    
}//end namespace ustd

#endif //__IOMANIP_HEADER
