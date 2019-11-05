// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.11.2013 21:46:01 CET
// File:    reset_sleep.cpp

#define COLOR_ON
#define DEBUG_ON

#include <Arduino.h>
#include <ustd.hpp>
#include <tool.hpp>
#include <util.hpp>

// you need to connect a button to pin 2 and GND and a button to pin 3 and GND

class program {
public:
    program(): timeout_(5) {
        setup();
    }
    void setup() {
        ustd::cout.init();
        ustd::cout << F("start reset_sleep.cpp") << ustd::endl;
        pinMode(2, INPUT_PULLUP); //I don't use a tool::button_class for this...
    }
    void update() {
        tool::clock.update();
        btn_.update();
    }
    void loop() {
        update();
        
        if(btn_ == state::falling) {
            ustd::cout << "reset" << ustd::endl;
            delay(100);
            util::reset(); //resets the whole program
        }
        
        if(tool::clock.sec() > timeout_) {
            ustd::cout << "sleep" << ustd::endl;
            timeout_ = tool::clock.sec() + 5;
            util::sleep(0, LOW /*default*/); //interrupt channel 0 (pin 2) to LOW brings the arduino back
            
            //drops below 1uA :D
            
            ustd::cout << "wake up" << ustd::endl;
        }
    }
private:
    tool::button_class<D3, LOW> btn_;
    double timeout_;
};

#include <main.hpp>
