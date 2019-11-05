// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    21.09.2013 21:13:55 CEST
// File:    stage1.cpp

#define COLOR_ON
//~ #define DEBUG_ON
#define ADVANCED_INTERRUPTS

#include <util/fast_io.hpp>
#include <Arduino.h>
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>

#include <device/CD4067.hpp>
#include <com/i2c.hpp>

class program {
public:
    program(): first_(0) {
        
        setup();
    }
    void setup() {
        ustd::cout.init();
        ustd::cout << F("start stage1.cpp") << ustd::endl;
        
        com::i2c_begin(66);
    }
    void update() {
        
        tool::clock.update();
        
        #define BTN_UP(x) b ## x ## _.update(); ar_[x - 3] = b ## x ## _.state();
        
        
        BTN_UP(3)
        BTN_UP(4)
        BTN_UP(5)
        BTN_UP(6)
        BTN_UP(7)
        BTN_UP(8)
        
        mux_.update();
        mux_.copy(ar_, 6);
        
        btn_.update();
        ar_[26] = btn_.state();
        
        x_.update();
        joystick_[0].update(x_.intervall(800, 1023));
        joystick_[1].update(x_.intervall(0, 223));
        ar_[22] = joystick_[0].state();
        ar_[23] = joystick_[1].state();
        
        y_.update();
        joystick_[2].update(y_.intervall(800, 1023));
        joystick_[3].update(y_.intervall(0, 223));
        ar_[24] = joystick_[2].state();
        ar_[25] = joystick_[3].state();
        
    }
    void loop() {
        cli(); //don't interrupt the update process
        update();
        sei(); //now interrupts are ok again
        
        //loop runs (free) at 1kHz
        
        wait_ = true;
        while(wait_) {delay(1);}
    }
    void receive(int n) {
        
    }
    void request() {
        if(first_ == 0) {
            com::i2cout << ar_ << ustd::endl;
            ++first_;
        } else if(first_ == 1) {
            com::i2cout << tool::clock << ustd::endl;
            --first_;
            wait_ = false;
        }
    }
private:
    int first_;
    ustd::array<uint8_t, 27> ar_; //TODO: glob::n_keys
    device::CD4067_class<13, 12, 11, 10, 9> mux_;
    
//------------------- axis buttons -------------------
    #define BTN(x) tool::button_class<x, LOW> b ## x ## _;
    
    BTN(3)
    BTN(4)
    BTN(5)
    BTN(6)
    BTN(7)
    BTN(8)
//------------------- joystick -------------------
    tool::analog_class<A0> x_;
    tool::analog_class<A1> y_;
    tool::button_class<A2, LOW> btn_;
    ustd::array<tool::fake_button_class, 4> joystick_;
    
    bool wait_;
};

#include <main.hpp>
