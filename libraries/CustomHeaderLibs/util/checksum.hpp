// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.06.2013 17:18:44 EDT
// File:    checksum.hpp

#ifndef __CHECKSUM_HEADER
#define __CHECKSUM_HEADER

//------------------- checksum generator -------------------
template<typename T>
uint8_t checksum(T const & t) {
    uint8_t res = 0;
    uint8_t const * const p = (uint8_t*)(&t);
    for(uint16_t i = 0; i < sizeof(t); ++i) {
        res += p[i];
    }
    return res;
}

#endif //__CHECKSUM_HEADER
