// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.06.2013 20:34:36 EDT
// File:    glove_master.cpp

#define COLOR_ON
#define DEBUG_ON
#define ADVANCED_INTERRUPTS

#include <Arduino.h>
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>
#include <com/i2c.hpp>
#include <com/uart.hpp>
#include "bridge.hpp"

com::i2cin_class i2cin;
com::i2cout_class i2cout;

com::uart_class_template<HardwareSerial> uart(Serial);

class program {
public:
    program(): c(66) {
        setup();
    }
    void setup() {
        ustd::cout.init();
        com::i2c_begin();
        //~ ustd::cout << F("start glove_master.cpp") << ustd::endl;
        
        led_ = state::blink;
    }
    void update() {
        tool::clock.update();
        led_.update();
        btn_.update();
        analog_.update();
    }
    void loop() {
        update();
        
        //~ uart >> i2c;
        //~ uart << i2c; //i2c >> uart;
        
        if(uart) {
            uart >> in;
            
            if(in == 'w') {
                uart >> vec_;
                i2cout(2) << in << vec_ << ustd::endl;
            }
            if(in == 'r') {
                i2cout(2) << in << ustd::endl;
                delayMicroseconds(100);
                i2cin(2) >> vec_;
                uart << vec_;
            }
            if(in == 's') {
                i2cout(2) << in << ustd::endl;
            }
        }
        
    }
private:
    uint8_t c;
    tool::light_class<13> led_;
    tool::button_class<2, LOW> btn_;
    tool::analog_class<A0> analog_;
    gesture_class g;
};

#include <main.hpp>
