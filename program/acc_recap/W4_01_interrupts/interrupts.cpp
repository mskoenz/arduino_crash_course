// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    07.11.2013 10:51:39 CET
// File:    interrupts.cpp

#include <Arduino.h>

// main idea:   -interrupts can be triggered by interrupt sources
//              -if triggered a functions (interrupt handler) gets executed immediatly
//              -main code stots at current possition
//              -clock doesn't run during interrupt (!!!delay, Serial and all timing based code doesn't work!!!)
//              -after the interrupt handler returns the main code continues where it was interrupted
//              -ATMega328p has two external interrupts
//              -pin 2 is interrupt 0
//              -pin 3 is interrupt 1
//              -you will observe deprelling problems in this example
//              -if you hit the button, the led will change state

// connect:     -led to GND and pin 13
//              -button to GND and pin 2
            

bool volatile state = LOW; //if you have trouble with interrupts, put volatile infront of all stuff that is affected by the interrupt / prevents compiler to optimize under assertion that the value is only changed in main code (normally with -Os volatile isn't needed)

int button_hits = 0; //count how many times the button was hit in order to see the deprelling problem

void change_blink() { //without my ADVANCED_INTERRUPTS (see next example) this function cannot be in the class
    state = !state;
    digitalWrite(13, state);
    //a delay(2) would get rid of deprelling, but delays aren't possible in an interrupt handler
    //Serial.println() will not work here
    ++button_hits;
}

class program {
public:
    program(): led_(13), btn_(2) {
        setup();
    }
    void setup() {
        Serial.begin(460800);
        
        pinMode(led_, OUTPUT);
        pinMode(btn_, INPUT_PULLUP);
        
        //attachInterrupt(interrupt channel, only void function accepted, mode (CHANGE, RISING, FALLING, LOW));
        attachInterrupt(0, change_blink, FALLING); //interrupt 0 is pin 2
    }
    void loop() {
        Serial.println(button_hits); //see deprelling
        delay(100); //even if the main code "sleeps" in a delay, an interrupt will happen immediatly
    }
private:
    uint8_t const led_; //uint8_t just to save space
    uint8_t const btn_;
    
};

#include <main.hpp>
