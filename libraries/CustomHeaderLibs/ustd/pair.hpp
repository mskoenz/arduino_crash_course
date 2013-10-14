// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    13.09.2013 20:26:47 CEST
// File:    pair.hpp

#ifndef __PAIR_HEADER
#define __PAIR_HEADER

namespace ustd {
    template<typename T, typename U>
    struct pair {
        typedef T first_type;
        typedef U second_type;
        
        //------------------- ctors -------------------
        pair(): first(), second() {
        }
        pair(T const & f, U const & s): first(f), second(s) {
        }
        
        //------------------- data -------------------
        first_type first;
        second_type second;
        
        //------------------- print and serialize -------------------
        template<typename S>
        void print(S & os) const {
            os << F("[") << first << F(", ") << second << F("]");
        }
        template<typename Archive>
        void serialize(Archive & ar) {
            ar & first;
            ar & second;
        }
    };
    
    template<typename T, typename U>
    pair<T, U> make_pair(T const & t, U const & u) {
        return pair<T, U>(t, u);
    }
}//end namespace ustd

#endif //__PAIR_HEADER
