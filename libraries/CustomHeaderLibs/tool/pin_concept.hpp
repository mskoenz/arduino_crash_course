// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.11.2013 01:16:15 CET
// File:    pin_concept.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __PIN_CONCEPT_HEADER
#define __PIN_CONCEPT_HEADER

#include "../ustd/ard_assert.hpp"

namespace tool {
    template<uint8_t pin>
    class intern {
    public:
        void mode(uint8_t const & pm) {
            pinMode(pin, pm);
        }
        void write(bool const & state) {
            digitalWrite(pin, state);
        }
        bool read() {
            return digitalRead(pin);
        }
    private:
        
    };
    
    class fake {
    public:
        void mode(uint8_t const & pm) {
        }
        void write(bool const & state) {
            ASSERT_MSG(false, "don't use write of the fake pin")
        }
        bool read() {
            ASSERT_MSG(false, "don't use read of the fake pin")
            return false;
        }
    private:
        
    };
}//end namespace tool

#endif //__PIN_CONCEPT_HEADER
