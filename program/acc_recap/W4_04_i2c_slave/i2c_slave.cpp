// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    07.11.2013 11:08:34 CET
// File:    i2c_slave.cpp

#include <Arduino.h>
#include <Wire.h>

// main idea:   -the master sends an i2c command to the slave
//              -slave will incr or decr a global_val
//              -the led indicates if the global_val is odd or even
//              -the master can request the global_val and the slave has to send it


// connect:     -led to GND and pin 13
//              -A4 to A4 of master SDA
//              -A5 to A5 of master SCL
//          
// if atmega only:
//              -XTL1 and XTL2 to 16MHz crystall (or to XTL1/2 of another off board chip)
//              -18pF cap form XTL1 to GND
//              -18pF cap form XTL2 to GND
//              -reset to empty arduino board reset
//              -TX to empty arduino board TX
//              -RX to empty arduino board RX


uint8_t global_val = 0; // only one byte so it's easy to serialize
uint8_t const global_led = 13; // ugly global stuff for now

void read_i2c(int i) { //doesn't seem to be an interrupt (Serial works)
    // if the master sends a command, read and execute it
    uint8_t cmd = Wire.read();
    
    if(cmd == '+')
        ++global_val;
    else if(cmd == '-')
        --global_val;
        
    digitalWrite(global_led, global_val & 1); // &1 == %2
}
void write_i2c() { //is an interrupt
    // if the master asks for data, send global_val
    Wire.write(global_val);
}

class program {
public:
    program() {
        setup();
    }
    void setup() {
    //------------------- set pinmodes and init -------------------
        pinMode(global_led, OUTPUT);
        digitalWrite(global_led, HIGH);
    //------------------- init i2c slave -------------------
        //join the i2c bus with adress 66
        Wire.begin(66); //adress in 16-127 / 0-15 mustn't be used (special commands)
        Wire.onReceive(read_i2c);
        Wire.onRequest(write_i2c);
    }
    void loop() {
        //do nothing
    }
private:
};

#include <main.hpp>
