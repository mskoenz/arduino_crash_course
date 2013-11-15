// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.11.2013 21:39:28 CET
// File:    sleep.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __SLEEP_HEADER
#define __SLEEP_HEADER

#include <Arduino.h>
#include <avr/sleep.h>

namespace util {
    void wake_up() {
        //nothing to do
    }

    void sleep(uint8_t const & interrupt_channel, uint8_t const & state = LOW) {
        uint8_t adcsra_save = ADCSRA;
        uint8_t prr_save = PRR;
        
        attachInterrupt(interrupt_channel, wake_up, state);
        
        ADCSRA = 0; // disable ADC

        PRR = 0b11101111; //diverse power saving settings

        set_sleep_mode (SLEEP_MODE_PWR_DOWN);
        sleep_enable();
     
        // turn off brown-out enable in software
        MCUCR = _BV (BODS) | _BV (BODSE);
        MCUCR = _BV (BODS); 
        sleep_cpu(); // != sleep_mode(); sleep_mode doesn't disable brown-out
        
        //sleep here
        
        ADCSRA = adcsra_save;
        PRR = prr_save;
        
        sleep_disable();
        detachInterrupt(interrupt_channel);
    }
}//end namespace util

#endif //__SLEEP_HEADER
