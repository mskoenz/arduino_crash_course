// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.06.2013 20:34:29 EDT
// File:    glove_slave.cpp

#define COLOR_ON
#define DEBUG_ON
#define ADVANCED_INTERRUPTS

#include <Arduino.h>
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>
#include <com/i2c.hpp>
#include <com/eeprom.hpp>
#include "bridge.hpp"

com::i2cin_class i2cin;
com::i2cout_class i2cout;


void on_receive(int N) {
    digitalWrite(13, HIGH);
    i2cin >> in;
    if(in == 'w') {
        i2cin >> vec_;
    }
    if(in == 'r') {
        i2cout << vec_;
    }
    if(in == 's') {
        com::eeprom << vec_;
    }
    digitalWrite(13, LOW);
}
void on_request() {
    i2cout << ustd::endl;
}


class program {
public:
    program() {
        setup();
    }
    void setup() {
        ustd::cout.init();
        com::i2c_begin(2, on_request, on_receive);
        //~ ustd::cout << F("start glove_slave.cpp") << ustd::endl;
        com::eeprom & vec_;
        
        diag::ram_report();
        
        led_ = state::off;
    }
    void update() {
        tool::clock.update();
        led_.update();
        btn_.update();
    }
    void loop() {
        if(btn_ == state::falling) {
            digitalWrite(13, HIGH);
            for(uint8_t i = 0; i < 10; ++i)
                ++vec_.lower_[i];
            digitalWrite(13, LOW);
        }
        update();
    }
private:
    tool::light_class<13> led_;
    tool::button_class<2, LOW> btn_;
};

#include <main.hpp>
