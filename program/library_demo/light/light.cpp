// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.11.2013 20:31:12 CET
// File:    light.cpp

#define COLOR_ON
#define DEBUG_ON

#include <Arduino.h>
#include <ustd.hpp>
#include <tool.hpp>

// you need to connect an LED to pin 13 and GND

class program {
public:
    program() {
        setup();
    }
    void setup() {
        ustd::cout.init();
        ustd::cout << F("start light.cpp") << ustd::endl;
        
        led_ = state::off;
        led_ = state::on;
        led_ = state::flash;    // 100 msec on / 900 msec off
        led_ = state::slow;     // 1 sec    on / 1 sec    off
        led_ = state::blink;    // 500 msec on / 500 msec off
        led_ = state::fast;     // 250 msec on / 250 msec off
        led_ = state::very_fast;// 10  msec on / 90  msec off
    }
    void update() {
        tool::clock.update();
        led_.update();
    }
    void loop() {
        update();
    }
private:
    tool::light_class<D13   // the pin
                    , HIGH  // means the LED shines if the pin is HIGH / default = HIGH
                     > led_;
};

#include <main.hpp>
