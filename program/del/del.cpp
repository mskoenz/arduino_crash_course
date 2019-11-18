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

void digiwrite() {
    for(uint32_t i = 0; i < 16; ++i) {
        digitalWrite(13, HIGH);
    }
}

class program {
public:
    program() {
        setup();
    }
    void setup() {
        ustd::cout.init(230400);
        pinMode(6, OUTPUT);
        analogWrite(6, 125);
        ustd::cout << F("start del.cpp") << ustd::endl;
        led_ = state::on;
        duty_ = 0;
    }
    void update() {
        tool::clock.update();
        // tool::clock.delay_to_hz(5000);
        // led_.update();
        // duty_ = (tool::clock.sec()*500)%10000;
        // // std::cout << duty_ << std::endl;
        // led_ = tool::clock.usec(10000) < duty_;
    }
    void loop() {
        update();
        // diag::speed_report();
    }
private:
    tool::light_class<D13, HIGH> led_;
    int duty_;
};

#include <main.hpp>
