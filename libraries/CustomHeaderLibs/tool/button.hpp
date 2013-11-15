// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.06.2013 17:31:25 EDT
// File:    button.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __BUTTON_HEADER
#define __BUTTON_HEADER

#include "clock.hpp"

#include <Arduino.h>
#include "../ustd/type_traits.hpp"
#include "pin_concept.hpp"

namespace state {
    enum button_enum : uint8_t {
          released = 1
        , pressed = 2
        , falling = 4
        , raising = 8
        , changed = (falling | raising)
        , auto_falling = 16
    };
    uint8_t const auto_rate = 30; //auto_falling per second
    uint16_t const auto_delay = 500; //in millis
}//end namespace state

namespace tool {
    template<typename pin_concept, bool pressed_state = HIGH, uint16_t _auto_rate = state::auto_rate, uint16_t _auto_delay = state::auto_delay>
    class button_class {
        typedef uint8_t state_type;
    public:
        //------------------- ctors -------------------
        button_class(): start_(0), state_(state::released), old_read_(!pressed_state) {
            if(pressed_state)
                pin_.mode(INPUT);
            else
                pin_.mode(INPUT_PULLUP);
        }
        template<typename T>
        button_class(T & t): start_(0), state_(state::released), old_read_(!pressed_state), pin_(t) {
            if(pressed_state)
                pin_.mode(INPUT);
            else
                pin_.mode(INPUT_PULLUP);
        }
        operator bool() const {
            return state_ == state::pressed;
        }
    private:
        //------------------- update implementation -------------------
        void update_impl(bool const & read) {
            if(state_ & (state::falling | state::auto_falling)) {
                state_ = state::pressed;
                return;
            }
            if(state_ & state::raising) {
                state_ = state::released;
                return;
            }
            if(state_ & state::pressed) {
                if((tool::clock.micros() - start_press_) > (1000000.0 / _auto_rate)) {
                    start_press_ = tool::clock.micros();
                    state_ = (state::auto_falling + state::pressed);
                }
            }
            
            if(read != old_read_) {
                if(start_ == 0)
                    start_ = tool::clock.micros();
                else
                    if(tool::clock.micros() - start_ > 2000u) {
                        state_ <<= 2; //brings pressed -> raising and released -> falling
                        start_press_ = tool::clock.micros() + _auto_delay * 1000.0;
                        old_read_ = read;
                    }
            }
            else
                start_ = 0;
        }
    public:
        //------------------- update -------------------
        template<typename T = void>
        typename ustd::enable_if<!ustd::is_same<pin_concept, fake>::value, T>::type update() {
            update_impl(pin_.read());
        }
        template<typename T = void>
        typename ustd::enable_if<ustd::is_same<pin_concept, fake>::value, T>::type update(bool const & read) {
            update_impl(read);
        }
        //------------------- getter -------------------
        state_type state() const {
            return state_;
        }
        //------------------- compare operator -------------------
        bool operator==(state_type const & arg) {
            return arg & state_;
        }
    private:
        double start_;
        double start_press_;
        state_type state_;
        bool old_read_;
        
        pin_concept pin_;
    };
    
}//end namespace tool

#endif //__BUTTON_HEADER
