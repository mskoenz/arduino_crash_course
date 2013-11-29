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
        void tone(uint16_t const & note, uint16_t const & dur) {
            ::tone(pin, note, dur);
        }
        void tone(uint16_t const & note) {
            ::tone(pin, note);
        }
        void no_tone() {
            ::noTone(pin);
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

//------------------- some abbreviations -------------------
typedef tool::intern<0> D0;
typedef tool::intern<1> D1;
typedef tool::intern<2> D2;
typedef tool::intern<3> D3;
typedef tool::intern<4> D4;
typedef tool::intern<5> D5;
typedef tool::intern<6> D6;
typedef tool::intern<7> D7;
typedef tool::intern<8> D8;
typedef tool::intern<9> D9;
typedef tool::intern<10> D10;
typedef tool::intern<11> D11;
typedef tool::intern<12> D12;
typedef tool::intern<13> D13;
typedef tool::intern<A0> DA0;
typedef tool::intern<A1> DA1;
typedef tool::intern<A2> DA2;
typedef tool::intern<A3> DA3;
typedef tool::intern<A4> DA4;
typedef tool::intern<A5> DA5;

#endif //__PIN_CONCEPT_HEADER
