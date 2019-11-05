// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.07.2013 15:35:23 EDT
// File:    out_pin.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __OUT_PIN_HEADER
#define __OUT_PIN_HEADER

#include <Arduino.h>
#include "./pin_concept.hpp"

namespace tool {
    template<typename pin_concept>
    class out_pin_class_base {
    public:
        //------------------- ctors -------------------
        out_pin_class_base(): state_(LOW) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, state_);
        }
        //------------------- ops -------------------
        operator bool() const {
            return state_;
        }
        //------------------- assignment -------------------
        out_pin_class_base & operator=(bool const & s) {
            state_ = s;
            digitalWrite(pin, state_);
            return (*this);
        }
        //------------------- modes -------------------
        void on() {
            state_ = HIGH;
            digitalWrite(pin, state_);
        }
        void off() {
            state_ = LOW;
            digitalWrite(pin, state_);
        }
        void flip() {
            state_ = !state_;
            digitalWrite(pin, state_);
        }
    private:
        bool state_;
        constexpr static uint8_t pin = pin_concept::physical_pin();
    };



    template<typename pin_concept>
    class out_pin_class: public out_pin_class_base<pin_concept> {
    };

    template<uint8_t pin>
    class out_pin_class<tool::intern<pin>>: public out_pin_class_base<tool::intern<pin>> {
    };

}//end namespace tool

#endif //__OUT_PIN_HEADER
