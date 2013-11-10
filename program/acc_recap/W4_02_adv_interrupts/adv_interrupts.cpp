// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    07.11.2013 10:55:47 CET
// File:    adv_interrupts.cpp

#define ADVANCED_INTERRUPTS

#include <Arduino.h>

// main idea:   -same as example befor but with nicer attachInterrupt functionality
//              -if you hit the button, the led will change state

// connect:     -led to GND and pin 13
//              -button to GND and pin 2
            
class program {
public:
    program(): led_(13), btn_(2), state_(LOW) {
        setup();
    }
    void setup() {
        pinMode(led_, OUTPUT);
        pinMode(btn_, INPUT_PULLUP);
        
        //attachInterrupt(interrupt channel, void function or function object accepted, mode (CHANGE, RISING, FALLING, LOW));
        
        //attachInterruptMethod(interrupt channel, void method of prgram class accepted, mode); //is a macro to hide method pointer syntax
        attachInterruptMethod(0, change_blink, FALLING); //attachInterruptMethod
    }
    void loop() {
        //nothing pollutes the loop
    }
    void change_blink() { //with the ADVANCED_INTERRUPTS (is not an arduino standart, I changed arduino.h)
        state_ = !state_;
        digitalWrite(13, state_);
    }
private:
    uint8_t const led_; //uint8_t just to save space
    uint8_t const btn_;
    bool state_; //works here without volatile 
};

#include <main.hpp>
