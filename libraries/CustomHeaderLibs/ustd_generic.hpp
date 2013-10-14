// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    14.06.2013 18:49:17 EDT
// File:    ustd_generic.hpp

#ifndef __USTD_GENERIC_HEADER
#define __USTD_GENERIC_HEADER

#ifndef F
    #define F(x) x
    #define STD_SUPPORT
#endif //F
//contains only stuff that doesn't need Arduino.h and avr

#include "ustd/pair.hpp"
#include "ustd/array.hpp"
#include "ustd/vector.hpp"
#include "ustd/string.hpp"
#include "ustd/filter.hpp"
//~ #include "ustd/bitset.hpp"
#include "ustd/ard_assert.hpp"
#include "ustd/fast_bitset.hpp"
#include "ustd/accumulator.hpp"
#include "ustd/static_vector.hpp"
#include "ustd/unordered_map.hpp"

#endif //__USTD_GENERIC_HEADER
