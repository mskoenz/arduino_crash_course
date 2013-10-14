// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.07.2013 15:35:23 EDT
// File:    out_pin.hpp

#ifndef __OUT_PIN_HEADER
#define __OUT_PIN_HEADER

#include <Arduino.h>

namespace tool {
    template<uint8_t pin>
    class out_pin_class {
    public:
        //------------------- ctors -------------------
        out_pin_class(): state_(LOW) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, state_);
        }
        //------------------- ops -------------------
        operator bool() const {
            return state_;
        }
        //------------------- assignment -------------------
        out_pin_class & operator=(bool const & s) {
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
    };
}//end namespace tool

#endif //__OUT_PIN_HEADER
