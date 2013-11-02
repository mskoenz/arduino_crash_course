// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2013 14:47:15 CET
// File:    uart_master.cpp

#include <Arduino.h>

// main idea: -reaction test between two player, each player has an arduino
//            -the master presses a start_button that starts a random delay
//            -after the delay an led lights up at the slave board
//            -both player need to press their button asap
//            -faster player wins -> win_led lights up on his board
//            -master can initialize another game with the start_button

// connect: button to GND and pin 2
//          button to GND and pin 3
//          led to GND and pin 13
//          pin 0 with pin 1 of the uart_slave
//          pin 1 with pin 0 of the uart_slave


class program {
public:
    program(): btn_(2), btn_start_(3), led_(13) {
        setup();
    }
    void setup() {
        pinMode(btn_, INPUT_PULLUP);
        pinMode(btn_start_, INPUT_PULLUP);
        pinMode(led_, OUTPUT);
        
        digitalWrite(led_, LOW);
        
        Serial.begin(460800); //needs to be the same as slave
        randomSeed(analogRead(A0)); //an analogRead(X) on a unconnected pin is a good "random" source
        
        go_ = false;
    }

    void loop() {
        delay(1); //for stability
        
        if(!go_ and digitalRead(btn_start_) == LOW) {
            digitalWrite(led_, LOW);
            delay(random(5) * 1000);
            Serial.write('g'); //tell the slave that the game begins
            go_ = true;
        }
        
        if(go_ and digitalRead(btn_) == LOW) {
            go_ = false;
            Serial.write('m'); //tell the slave that master won
            digitalWrite(led_, HIGH);
        }
        
        if(Serial.available() > 0) { //listen to the slave
            char in = Serial.read();
            
            if(in == 's') { //slave wins
                go_ = false;
            }
        }
    }        
private:
    bool go_;
    uint8_t const btn_;
    uint8_t const btn_start_;
    uint8_t const led_;
};

#include <main.hpp>
