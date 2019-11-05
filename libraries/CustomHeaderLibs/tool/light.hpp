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

          default_mark = 0<<6
        , off = 0
        , on = 1
        , flash = 2
        , slow = 3
        , blink = 4
        , fast = 5
        , very_fast = 6

        , red_mark = 1<<6
        , red_on = red_mark | state::on
        , red_flash = red_mark | state::flash
        , red_slow = red_mark | state::slow
        , red_blink = red_mark | state::blink
        , red_fast = red_mark | state::fast
        , red_very_fast = red_mark | state::very_fast

        , green_mark = 2<<6
        , green_on = green_mark | state::on
        , green_flash = green_mark | state::flash
        , green_slow = green_mark | state::slow
        , green_blink = green_mark | state::blink
        , green_fast = green_mark | state::fast
        , green_very_fast = green_mark | state::very_fast

        , blue_mark = 3<<6
        , blue_on = blue_mark | state::on
        , blue_flash = blue_mark | state::flash
        , blue_slow = blue_mark | state::slow
        , blue_blink = blue_mark | state::blink
        , blue_fast = blue_mark | state::fast
        , blue_very_fast = blue_mark | state::very_fast
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
        void sleep() {
            pin_.write(!on_state);
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

    template<typename pin_concept_red, typename pin_concept_green, typename pin_concept_blue, bool on_state = HIGH>
    class rgb_light_class {
    public:
        rgb_light_class(): red_(), green_(), blue_() {
        }
        rgb_light_class & operator=(state::light_enum const & s) {
            uint8_t col = s & (3<<6);
            uint8_t last_col = state_ & (3<<6);
            state_ = s;

            set_led(last_col, state::off);
            set_led(col, state::light_enum(state_ & (~(3<<6))));

            return (*this);
        }
        void update() {
            red_.update();
            green_.update();
            blue_.update();
        }
        void sleep() {
            red_.sleep();
            green_.sleep();
            blue_.sleep();
        }
    private:
        void set_led(uint8_t const & col, state::light_enum state) {
            if(col == state::red_mark or col == state::default_mark) {
                red_ = state;
            } else if(col == state::green_mark) {
                green_ = state;
            } else if(col ==  state::blue_mark) {
                blue_ = state;
            }
        }
        state::light_enum state_;
        light_class<pin_concept_red, on_state> red_;
        light_class<pin_concept_green, on_state> green_;
        light_class<pin_concept_blue, on_state> blue_;
    };
}//end namespace tool

#endif //__LIGHT_HEADER
