// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    20.07.2013 11:26:54 EDT
// File:    tags.hpp

#ifndef __ACCUMULATOR_TAGS_HEADER
#define __ACCUMULATOR_TAGS_HEADER

//------------------- remove arduino macros -------------------
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace ustd {
    namespace tag {
        struct count {};
        struct mean {};
        struct error {};
        struct min {};
        struct max {};
        template<int N>
        struct ema {}; //exponentially moving average
    }//end namespace tag
}//end namespace ustd 

#endif //__ACCUMULATOR_TAGS_HEADER
