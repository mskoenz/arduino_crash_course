// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.10.2013 01:07:01 CEST
// File:    empty template.cpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#define COLOR_ON
#define DEBUG_ON
#define ADVANCED_INTERRUPTS

#include <Arduino.h>
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>

class program {
public:
    using T = uint8_t;
    program() {
        setup();
        //~ x_[0].push_back(255);
        //~ x_[0].push_back(255);
        //~ x_[0].push_back(255);
        //~ x_[8].push_back(255);
        //~ x_[5].push_back(255);
        
        //~ x_.push_back(ustd::vector<T>());
        //~ x_.push_back(ustd::vector<T>());
        //~ x_[0].push_back(255);
        //~ x_[0].push_back(255);
        //~ x_[1].push_back(255);
        
        //~ for(uint8_t i = 0; i < x_.size(); ++i) {
            //~ ustd::cout << (uint16_t)x_[i].data() << ustd::endl;
        //~ }
        
    }
    void setup() {
        ustd::cout.init(115200);
        diag::ram_report();
        diag::print_stack();
        
        DEBUG_MSG("start")
        
        diag::ram_report();
        diag::print_stack();
        
        ustd::cout << *b << ustd::endl;
    }
    void loop() {
    }
private:
    //~ ustd::vector<ustd::vector<T>> x_;
};

#include <main.hpp>
