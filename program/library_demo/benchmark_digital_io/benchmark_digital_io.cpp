// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    25.10.2013 18:12:20 CEST
// File:    benchmark_digital_io.cpp

#define DEBUG_ON
#define COLOR_ON

//include this header as first one to speed up digital io
//~ #include <util/fast_io.hpp> 

#include <Arduino.h>
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>

// you only need the arduino board for this

// NOTE: here only setup/loop fct are defined, no program_class
// instead of main.hpp, main.cpp is included.
// it looks simpler but isn't as nice as the program_class version in terms of design (imho)

int const po = 13;
int const pi = 12;

void setup() {
    ustd::cout.init();
    pinMode(po, OUTPUT);
    pinMode(pi, INPUT_PULLUP);
    
    // benchmark report accepts a lambda-function
    diag::benchmark_report([](){digitalRead(pi);});
    diag::benchmark_report([](){digitalWrite(po, HIGH);});
    diag::benchmark_report([](){analogRead(A0);});
    
    // this outputs the RAM status at this time
    // NOTE: if you have dynamic structures/recursions it matters very much when you call this
    diag::ram_report();
}

void loop() {
    //just some load in the loop
    delay(1);
    //clock is a global clock and the speed_report needs this clock
    tool::clock.update();
    //outputs every 1-3 s the looptime and frequency. Has a fairly small overhead
    diag::speed_report();
}

#include <main.cpp>
