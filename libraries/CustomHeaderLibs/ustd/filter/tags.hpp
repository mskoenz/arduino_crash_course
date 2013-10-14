// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    23.07.2013 05:10:03 EDT
// File:    tags.hpp

#ifndef __FILTER_TAGS_HEADER
#define __FILTER_HEADER

namespace ustd {
    namespace tag {
        struct identity {};
        template<unsigned N>
        struct lowpass {};
        template<unsigned PROMIL>
        struct highpass {};
        template<unsigned W>
        struct hysteresis {};
        
    }//end namespace tag
}//end namespace ustd
#endif //__FILTER_HEADER
