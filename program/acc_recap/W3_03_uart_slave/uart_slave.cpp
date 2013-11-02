// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2013 14:47:19 CET
// File:    uart_slave.cpp

#include <Arduino.h>

// see uart_master for the main idea.

// connect: button to GND and pin 2
//          led to GND and pin 13
//          led to GND and pin 12
//          pin 0 with pin 1 of the uart_master
//          pin 1 with pin 0 of the uart_master

class program {
public:
    program(): btn_(2), led_(13), start_led_(12) {
        setup();
    }
    void setup() {
        pinMode(btn_, INPUT_PULLUP);
        pinMode(led_, OUTPUT);
        pinMode(start_led_, OUTPUT);
        
        digitalWrite(led_, LOW);
        digitalWrite(start_led_, LOW);
        
        Serial.begin(460800); //needs to be the same as master
        
        go_ = false;
    }

    void loop() {
        delay(1); //for stability
        
        if(go_ and digitalRead(btn_) == LOW) {
            go_ = false;
            Serial.write('s'); //tell master that slave won
            digitalWrite(led_, HIGH);
            digitalWrite(start_led_, LOW);
        }
        
        if(Serial.available() > 0) { //listen to master
            char in = Serial.read();
            
            if(in == 'g') { //master wants to start the game
                go_ = true;
                digitalWrite(led_, LOW);
                digitalWrite(start_led_, HIGH);
            }
            
            if(in == 'm') { //master won
                go_ = false;
                digitalWrite(start_led_, LOW);
            }
        }
    }        
private:
    bool go_;
    uint8_t const btn_;
    uint8_t const led_;
    uint8_t const start_led_;
};

#include <main.hpp>
