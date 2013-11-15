// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.06.2013 15:53:18 EDT
// File:    light.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __LIGHT_HEADER
#define __LIGHT_HEADER

#include "clock.hpp"

#include <Arduino.h>
#include "../ustd/ard_assert.hpp"
#include "../ustd/type_traits.hpp"
#include "pin_concept.hpp"

namespace state {
    enum light_enum : uint8_t {
          off
        , on
        , flash
        , slow
        , blink
        , fast
        , very_fast
    };
}//end namespace state

namespace tool {
    template<typename pin_concept, bool on_state = HIGH>
    class light_class {
    public:
        //------------------- ctors -------------------
        light_class(): state_(state::off) {
            pin_.mode(OUTPUT);
        }
        template<typename T>
        light_class(T & t): state_(state::off), pin_(t) {
            pin_.mode(OUTPUT);
        }
        //------------------- assignment -------------------
        template<class pin_concept2, bool on_state2>
        light_class & operator=(light_class<pin_concept2, on_state2> const & rhs) {
            state_ = rhs.state_;
            return (*this);
        }
        light_class & operator=(state::light_enum const & s) {
            state_ = s;
            return (*this);
        }
        light_class & operator=(bool const & s) {
            state_ = (s ? state::on : state::off);
            return (*this);
        }
        //------------------- modes -------------------
        void on() {
            pin_.write(on_state);
        }
        void off() {
            pin_.write(!on_state);
        }
        void flash() {
            pin_.write((tool::clock.msec() < 100) == on_state);
        }
        void fast() {
            pin_.write((tool::clock.msec(500) < 250) == on_state);
        }
        void very_fast() {
            pin_.write((tool::clock.msec(100) < 10) == on_state);
        }
        void blink() {
            pin_.write((tool::clock.msec(1000) < 500) == on_state);
        }
        void slow() {
            pin_.write((tool::clock.sec() & 1) == on_state);
        }
        //------------------- update -------------------
        void update() {
            #define UPDATE(STATE) if(state_ == state::STATE) STATE(); else
            
            UPDATE(on)
            UPDATE(off)
            UPDATE(flash)
            UPDATE(fast)
            UPDATE(blink)
            UPDATE(slow)
            UPDATE(very_fast)
            ; //last else
            
            #undef UPDATE
        }
        //------------------- getter -------------------
        state::light_enum const & state() const {
            return state_;
        }
        //------------------- ops -------------------
        void flip() {
            if(state_ == state::on)
                state_ = state::off;
            else if(state_ == state::off)
                state_ = state::on;
        }
    private:
        state::light_enum state_;
        pin_concept pin_;
    };
}//end namespace tool

#endif //__LIGHT_HEADER
