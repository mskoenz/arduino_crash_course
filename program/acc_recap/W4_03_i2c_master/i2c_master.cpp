// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    07.11.2013 11:08:28 CET
// File:    i2c_master.cpp

#include <Arduino.h>
#include <Wire.h>

// main idea:   -the master sends an i2c command to the slave
//              -the command is + or - depending on what button was pressed
//              -slave will incr or decr a global_val
//              -the master can request the global_val and the slave has to send it

// connect:     -button to GND (or pin 8 or pin 9) and pin 6
// connect:     -button to GND (or pin 8 or pin 9) and pin 11
//              -A4 to A4 of slave SDA
//              -A5 to A5 of slave SCL
//          
// if atmega only:
//              -XTL1 and XTL2 to 16MHz crystall (or to XTL1/2 of another off board chip)
//              -18pF cap form XTL1 to GND
//              -18pF cap form XTL2 to GND
//              -reset to empty arduino board reset
//              -TX to empty arduino board TX
//              -RX to empty arduino board RX

class program {
public:
    program(): btn_up_(6), btn_down_(11), myres_(0) {
        setup();
    }
    void setup() {
        Serial.begin(460800);
    //------------------- set pinmodes and init -------------------
        pinMode(btn_up_, INPUT_PULLUP);
        pinMode(btn_down_, INPUT_PULLUP);
        pinMode(8, OUTPUT); // I just use 8 and 9 as ground
        pinMode(9, OUTPUT);
        
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
    //------------------- init i2c master -------------------
        Wire.begin(); // master doesn't need an adress (optional)
        
    }
    void loop() {
        if(digitalRead(btn_up_) == LOW) {
            Wire.beginTransmission(66);
            Wire.write('+');
            Wire.endTransmission();
            ++myres_;
            
            Wire.requestFrom(66, 1); // from adress 66 one byte
            Serial.print((int)Wire.read());
            Serial.print(" ");
            Serial.println(myres_);
            
            delay(100);
        }
        
        if(digitalRead(btn_down_) == LOW) {
            Wire.beginTransmission(66);
            Wire.write('-');
            Wire.endTransmission();
            --myres_;
            
            Wire.requestFrom(66, 1); // from adress 66 one byte
            
            Serial.print((int)Wire.read());
            Serial.print(" ");
            Serial.println(myres_);
            
            delay(100);
        }
    }
private:
    uint8_t myres_;
    int const btn_up_;
    int const btn_down_;
    
};

#include <main.hpp>
