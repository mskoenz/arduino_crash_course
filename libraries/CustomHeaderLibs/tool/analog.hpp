// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    08.07.2013 21:21:42 EDT
// File:    analog.hpp

#ifndef __ANALOG_HEADER
#define __ANALOG_HEADER

#include <Arduino.h>

#include <ustd/filter.hpp>

namespace tool {
    template<uint8_t pin, unsigned N = 4, unsigned W = 1>
    class analog_class {
        typedef int16_t value_type;
    public:
        analog_class() {
            for(unsigned i = 0; i < 2*N; ++i) {
                update(); //warm up
            }
        }
        operator value_type() const {
            return f;
        }
        void update() {
            f << analogRead(pin);
        }
        bool intervall(value_type const & low, value_type const & high) {
            if(f > low and f < high)
                return true;
            return false;
        }
    private:
        ustd::filter<value_type, ustd::tag::hysteresis<W>, ustd::tag::lowpass<N>> f;
    };
}//end namespace tool

#endif //__ANALOG_HEADER
