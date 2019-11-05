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
#include <com/i2c.hpp>
#include <device/MMA8452.hpp>

class program {
public:
    program() {
        setup();
    }
    void setup() {
        ustd::cout.init();
        com::i2c_begin(0);
        gmeter_.init(8);
        ustd::cout << F("start del.cpp") << ustd::endl;
    }
    void update() {
        tool::clock.update();
        btn1_.update();
        btn2_.update();
        led_.update();
        gmeter_.update();
        btn3_.update(gmeter_.y() > 3);
    }
    void loop() {
        update();
        
        if(btn1_ == state::falling)
            led_ = state::on;
            
        if(btn1_ == state::rising)
            led_ = state::off;
            
        if(btn3_ == state::falling) {
            led_.flip();
            delay(30);
            ustd::cout << "flip" << tool::clock.msec() << ustd::endl;
        }
    }
    int request() {
    }
    void receive(int) {
    }
private:
    tool::button_class<D2, LOW> btn1_;
    tool::button_class<D3, LOW> btn2_;
    tool::button_class<tool::fake> btn3_;
    tool::light_class<D7> led_;
    device::MMA8452_class gmeter_;
};

#include <main.hpp>
