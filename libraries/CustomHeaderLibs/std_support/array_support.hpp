// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.06.2013 23:34:04 EDT
// File:    array_support.hpp

#ifndef __ARRAY_SUPPORT_HEADER
#define __ARRAY_SUPPORT_HEADER

#include <array>

//------------------- print & serialize -------------------
template<typename T, size_t N, typename S>
S & operator<<(S & os, std::array<T, N> const & arg) {
    os << "[";
    for(size_t i = 0; i < N; ++i) {
        os << arg[i];
        if(i != N - 1)
            os << ", ";
    }
    os << "]";
    return os;
}
namespace com {
    template<typename T, size_t N, typename Archive>
    void serialize(Archive & ar, std::array<T, N> & arg) {
        for(size_t i = 0; i < N; ++i) {
            ar & arg[i];
        }
    }
}//end namespace com

#endif //__ARRAY_SUPPORT_HEADER
