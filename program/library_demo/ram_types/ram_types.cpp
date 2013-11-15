// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    25.10.2013 18:16:01 CEST
// File:    ram_types.cpp

#define COLOR_ON
#define DEBUG_ON

#include <Arduino.h>
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>

// you need to connect a button to pin 2 and GND
// uncomment the parts that you want to test (lines 44/45 for static effects and lines 58/59 for dynamic (use button) effects) if you decomment the stack_demo and both static line you can see a heap stack collision :-) mostly it behaves like a reset, but no always

double _bla;

//gets optmized away if line 44 is commented
char const lore_ipsum[] = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.";

//gets optmized away if line 45 is commented
uint8_t big_array[1000];

class program {
public:
    program(): count_(0) {
        setup();
    }
    void rec(uint16_t bla) {
        if(bla == 0) {
            ustd::cout << _bla << ustd::endl;
            _bla = 0;
            diag::ram_report();
        }
        else
            rec(bla - 1);
        _bla += bla;
    }
    
    void setup() {
        ustd::cout.init();
        ustd::cout << F("start del.cpp") << ustd::endl;
        
        //~ data_demo();
        //~ bss_demo();
        
        diag::ram_report();
    }
    void update() {
        tool::clock.update();
        btn_.update();
    }
    void loop() {
        update();
        if(btn_ == state::falling) {
            ustd::cout << CLRSCR;
            
            //~ stack_demo();
            //~ heap_demo();
            
            count_ <<= 1;
            if(count_ == 0)
                ++count_;
        }
    }
    void stack_demo() {
        //start a massive recursion
        rec(4*count_);
        ustd::cout << ustd::endl;
    }
    void heap_demo() {
        vec_.clear();
        vec_.push_back(2);
        //resize the vector (increase 8 to see a heap stack collision)
        vec_.resize(8*count_);
        //this is needed since a vector never gives up space once allocated
        vec_.shrink_to_fit();
        
        DEBUG_VAR(count_)
        diag::ram_report();
    }
    void data_demo() {
        ustd::cout << lore_ipsum << ustd::endl;
    }
    void bss_demo() {
        for(uint16_t i = 0; i < 1000; ++i) {
            ustd::cout << big_array[i] << " ";
        }
        ustd::cout << ustd::endl;
    }
private:
    uint8_t count_;
    tool::button_class<D2, LOW> btn_;
    ustd::vector<uint8_t> vec_;
};

#include <main.hpp>
