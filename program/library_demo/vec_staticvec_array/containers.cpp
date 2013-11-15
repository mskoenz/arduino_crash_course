// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.11.2013 21:05:38 CET
// File:    containers.cpp

#define COLOR_ON
#define DEBUG_ON

#include <Arduino.h>
#include <ustd.hpp>

// you only need the arduino

class program {
public:
    program(): vec_(10, 42) { //init vector with 10 elements with value 42
        setup();
    }
    void setup() {
        ustd::cout.init();
        ustd::cout << F("start containers.cpp") << ustd::endl;
        
        svec_.push_back(12);
        svec_.push_back(13);
        svec_.push_back(14);
        
        arr_[4] = 66;
        
        ustd::cout << vec_ << ustd::endl;
        ustd::cout << svec_ << ustd::endl;
        ustd::cout << arr_ << ustd::endl;
        
        //iterators not online yet..
        //~ for(auto x : arr_) //awesome c++11 stuff :D
            //~ ustd::cout << x << " ";
        //~ ustd::cout << ustd::endl;
    }
    void update() {
    }
    void loop() {
        update();
    }
private:
    ustd::vector<uint8_t> vec_;
    ustd::static_vector<uint8_t, 8> svec_;
    ustd::array<uint8_t, 8> arr_;
};

#include <main.hpp>
