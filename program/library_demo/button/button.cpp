// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.11.2013 20:13:26 CET
// File:    button.cpp

#define COLOR_ON
#define DEBUG_ON

#include <Arduino.h>
#include <ustd.hpp>
#include <tool.hpp>

// you need to connect a button to pin 2 and GND

class program {
public:
    program() {
        setup();
    }
    void setup() {
        ustd::cout.init();
        ustd::cout << F("start button.cpp") << ustd::endl;
    }
    void update() {
        tool::clock.update();
        btn_.update();
    }
    void loop() {
        update();
        
        if(btn_ == state::falling)
            ustd::cout << F("falling") << ustd::endl;
        
        if(btn_ == state::rising)
            ustd::cout << F("rising") << ustd::endl;
        
        if(btn_ == state::changing)
            ustd::cout << F("changing") << ustd::endl;
        
        if(btn_ == state::pressed)
            ustd::cout << F(".");
        
        //released is also an option
        
        if(btn_ == state::auto_repeat)
            ustd::cout << F("auto_repeat") << ustd::endl;
        
        
        delay(4); //to prevent too many dots from pressed
    }
private:
    tool::button_class<D2   // the pin
                     , LOW  // LOW means button is pressed / default = HIGH
                     , 10   // #auto_repeat per sec / default = 30
                     , 200  // delay in msec before auto_repeat starts / default = 500
                      > btn_;
};

#include <main.hpp>
