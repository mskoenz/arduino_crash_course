// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    25.05.2013 17:17:06 EDT
// File:    rw_speed.cpp

#define DEBUG_ON
#define COLOR_ON

#include <diag.hpp>
#include <Arduino.h>
#include <ustd.hpp>
#include <fast_io.hpp>

int const po = 13;
int const pi = 12;

void setup() {
    ustd::cout.init();
    pinMode(po, OUTPUT);
    pinMode(pi, INPUT_PULLUP);
    
    diag::benchmark_report([](){digitalRead(pi);});
    diag::benchmark_report([](){digitalWrite(po, HIGH);});
    diag::ram_report();
}

uint8_t i = 0;

void loop() {
    delay(++i);
    diag::speed_report();
}
