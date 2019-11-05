// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.10.2013 01:07:01 CEST
// File:    empty template.cpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#include <Arduino.h>
#include <ustd.hpp>
#include <util.hpp>
#include <tool.hpp>

class program {
public:
    program(): count_(0) {
        setup();
    }
    void setup() {
        ustd::cout.init();
        ustd::cout << "Hello" << ustd::endl;
        green0_ = state::on;
        green1_ = state::on;
        green2_ = state::on;
        green3_ = state::on;
        
        red0_ = state::off;
        red1_ = state::off;
        red2_ = state::off;
        red3_ = state::off;
        
        bin0_ = state::off;
        bin1_ = state::off;
        bin2_ = state::off;
        bin3_ = state::off;
        bin4_ = state::off;
    }
    void update() {
        tool::clock.update();
        
        green0_.update();
        green1_.update();
        green2_.update();
        green3_.update();
        
        red0_.update();
        red1_.update();
        red2_.update();
        red3_.update();
        
        #define binup(x)                                                       \
        if((count_>>x) & 1)                                                    \
            bin##x##_ = state::on;                                             \
        else                                                                   \
            bin##x##_ = state::off;                                           //
        
        binup(0)
        binup(1)
        binup(2)
        binup(3)
        binup(4)
        
        bin0_.update();
        bin1_.update();
        bin2_.update();
        bin3_.update();
        bin4_.update();
        
        btnU_.update();
        btnD_.update();
        btnC_.update();
    }
    void loop() {
        update();
        
        if(btnU_ == state::falling) {
            ustd::cout << "UP" << analogRead(A0) << ustd::endl;
            green0_ = state::on;
            green1_ = state::on;
            green2_ = state::on;
            green3_ = state::on;
            
            red0_ = state::off;
            red1_ = state::off;
            red2_ = state::off;
            red3_ = state::off;
        }
        if(btnD_ == state::falling) {
            ustd::cout << "DOWN" << ustd::endl;
            red0_ = state::on;
            red1_ = state::on;
            red2_ = state::on;
            red3_ = state::on;
            
            green0_ = state::off;
            green1_ = state::off;
            green2_ = state::off;
            green3_ = state::off;
        }
        if(btnC_ == state::falling) {
            count_ += 1;
            ustd::cout << "CONFIRM" << ustd::endl;
        }
    }
private:
    uint8_t count_;

    tool::button_class<D4,  LOW> btnU_;
    tool::button_class<DA1, LOW> btnD_;
    tool::button_class<DA2, LOW> btnC_;
    
    tool::light_class<DA3> bin0_;
    tool::light_class<DA4> bin1_;
    tool::light_class<DA5> bin2_;
    tool::light_class<D2>  bin3_;
    tool::light_class<D3>  bin4_;
    
    tool::light_class<D12> green0_;
    tool::light_class<D11> green1_;
    tool::light_class<D10> green2_;
    tool::light_class<D9> green3_;
    
    tool::light_class<D8> red0_;
    tool::light_class<D7> red1_;
    tool::light_class<D6> red2_;
    tool::light_class<D5> red3_;
    
};

#include <main.hpp>
