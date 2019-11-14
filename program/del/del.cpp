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


quint16_t test_0() {
    uint16_t res = 0;
    volatile uint16_t add = 1;
    for(uint16_t i = 0; i < 1000; ++i) {
        add = 1;
        res += add;
    }
    return res;
}
uint16_t test_1() {
    uint16_t res = 0;
    volatile uint16_t add = 1;
    for(uint16_t i = 0; i < 1000; ++i) {
        add = micros();
        res += add;
    }
    return res;
}
uint16_t test_2() {
    tool::clock.update();
    volatile uint16_t add = 1;
    uint16_t res = 0;
    for(uint16_t i = 0; i < 1000; ++i) {
        add = tool::clock.micros();
        res += add;
    }
    return res;
}


class program {
public:
    program() {
        setup();
    }
    void setup() {
        ustd::cout.init(230400);
        ustd::cout << F("start del.cpp") << ustd::endl;
        led_ = state::blink;
    }
    void update() {
        tool::clock.update();
        tool::clock.delay_to_hz(250);
        led_.update();
    }
    void loop() {
        update();
        diag::benchmark_report(test_0, 10);
        diag::benchmark_report(test_1, 10);
        diag::benchmark_report(test_2, 10);
        // diag::benchmark_report(millis, 100000);
    }
private:
    tool::light_class<D13, LOW> led_;
};

#include <main.hpp>
