// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.11.2013 20:42:15 CET
// File:    iostream.cpp

#define COLOR_ON
#define DEBUG_ON

#include <Arduino.h>
#include <ustd.hpp>

// you only need the arduino

class program {
public:
    program() {
        setup();
    }
    void setup() {
        ustd::cout.init();
        ustd::cout << F("start iostream.cpp") << ustd::endl;
        
        //print next numbers in binary with leading 0
        
        ustd::cout << ustd::setbase(2) << ustd::setfill('0'); //set up the options
        
        ustd::cout  << ustd::setw(8) << 1 << " "
                    << ustd::setw(8) << 2 << " "
                    << ustd::setw(8) << 3 << " "
                    << ustd::setw(8) << 4 << " "
                    << ustd::setw(8) << 5 << " "
                    << ustd::setw(8) << 0XFF << ustd::endl;
        
        ustd::cout << ustd::setbase(10) << ustd::setfill(' '); //reset options
        
        //print next numbers in hex and in a color
        
        ustd::cout << ustd::setbase(16); //set up the options
        
        ustd::cout  << RED    << ustd::setw(3) << 0xAB << " "
                    << YELLOW << ustd::setw(3) << 0x5  << " "
                    << GREEN  << ustd::setw(3) << 0XFF << ustd::endl;
        
        ustd::cout << ustd::setbase(10) << NONE; //reset options
        
        //same in octal base but bold...
        
        ustd::cout << ustd::setbase(8); //set up the options
        
        ustd::cout  << REDB    << ustd::setw(3) << 0xAB << " "
                    << YELLOWB << ustd::setw(3) << 0x5  << " "
                    << GREENB  << ustd::setw(3) << 0XFF << ustd::endl;
        
        ustd::cout << ustd::setbase(10) << NONE; //reset options
        
        //...or just with a background color
        
        ustd::cout  << REDBG    << ustd::setw(3) << 0xAB << " "
                    << YELLOWBG << ustd::setw(3) << 0x5  << " "
                    << GREENBG  << ustd::setw(3) << 0XFF << " ";
        
        ustd::cout << NONE << ustd::endl; //reset options
    }
    void update() {
    }
    void loop() {
        update();
        
        int i;
        
        ustd::cout<< F("enter an integer: ") << ustd::endl;
        //for now only numbers (integers and floating points) and bools possible...
        ustd::cin >> i;
        
        ustd::cout << ustd::endl;
        ustd::cout << RED    << "DEC: " << REDB                         << ustd::setw(9) << i << ustd::endl;
        ustd::cout << YELLOW << "OCT: " << YELLOWB << ustd::setbase(8)  << ustd::setw(9) << i << ustd::endl;
        ustd::cout << CYAN   << "HEX: " << CYANB   << ustd::setbase(16) << ustd::setw(9) << i << ustd::endl;
        ustd::cout << GREEN  << "BIN: " << GREENB  << ustd::setbase(2)  << ustd::setw(9) << i << ustd::endl;
        ustd::cout << NONE << ustd::setbase(10);
    }
private:
};

#include <main.hpp>
