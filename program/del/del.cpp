// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    27.10.2014 12:25:06 CET
// File:    del.cpp

#define COLOR_ON
#define DEBUG_ON
#define ADVANCED_INTERRUPTS

#include <Arduino.h>
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>

class program {
public:
    program() {
        setup();
    }
    void setup() {
        ustd::cout.init();
        ustd::cout << F("start del.cpp") << ustd::endl;
        led_ = state::slow;
    }
    void update() {
        tool::clock.update();
        led_.update();
        btn_.update();
    }

    void loop() {
        update();

        if(btn_ == state::falling)
            led_ = state::on;

        if(btn_ == state::rising)
            led_ = state::flash;

    }
private:
    tool::light_class<D13, LOW> led_;
    tool::button_class<D2, LOW> btn_;
};

#include <main.hpp>
