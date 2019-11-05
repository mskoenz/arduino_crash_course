// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.06.2013 15:54:46 EDT
// File:    clock.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __CLOCK_HEADER
#define __CLOCK_HEADER

#include <Arduino.h>

namespace tool {
    class clock_class {
    public:
        //------------------- ctors -------------------
        clock_class(): now_us_(0), last_us_(0) {
        }
        //------------------- getter -------------------
        uint32_t sec() {
            return now_us_ / 1000000.0;
        }
        uint16_t msec(uint16_t const & mod = 1000) {
            return (now_us_ / 1000) % mod;
        }
        uint16_t usec(uint16_t const & mod) {
            return now_us_ % mod;
        }
        uint64_t micros() const {
            return now_us_;
        }
        uint32_t millis() const {
            return now_us_ / 1000.0;
        }
        //------------------- update -------------------
        void update() {
            last_us_ = now_us_;
            uint32_t measurement = ::micros();
            //works even if there is an overflow
            now_us_ += uint32_t(measurement - last_measurement_);
            last_measurement_ = measurement;
        }
        void delay_to_hz(uint16_t const & frequency_hz) {
            double us_in_sec = 1000000;
            uint16_t dt_target = us_in_sec/frequency_hz;
            uint16_t dt_real = uint16_t(now_us_ - last_us_);
            if(dt_target > dt_real) {
                uint16_t correct = dt_target-dt_real;
                delay(correct/1000);
                delayMicroseconds(correct%1000); // only supports max 16k
                // I need to update, since time changed
                // I'm greedy here and dont measure micros again (via update)
                last_us_ += correct;
                now_us_ += correct;
                last_measurement_ += correct;
                // update();
            }
        }
    private:
        uint64_t now_us_;
        uint64_t last_us_;
        uint32_t last_measurement_; // to fix overflow
    } clock;

    class timer_class {
    public:
        timer_class(): zero_ref_(0) {}
        uint32_t sec() {
            return (clock.micros() - zero_ref_) / 1000000.0;
        }
        uint16_t msec(uint16_t const & mod = 1000) {
            return ((clock.micros() - zero_ref_) / 1000) % mod;
        }
        uint16_t usec(uint16_t const & mod) {
            return (clock.micros() - zero_ref_) % mod;
        }
        uint64_t micros() const {
            return clock.micros() - zero_ref_;
        }
        uint32_t millis() const {
            return (clock.micros() - zero_ref_) / 1000.0;
        }
        /*===modifying methods===*/
        void reset() {
            zero_ref_ = clock.micros();
        }
        /*==== const methods ====*/
    private:
        uint64_t zero_ref_;
    };
}//end namespace tool

#endif //__CLOCK_HEADER
