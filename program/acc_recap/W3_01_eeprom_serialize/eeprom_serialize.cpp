// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2013 14:47:10 CET
// File:    eeprom_serialize.cpp

#include <Arduino.h>
#include <EEPROM.h> //don't forget this header


// main idea: -read and write to the EEPROM (is like a harddrive)
//            -EEPROM data remains even after the power is lost (no matter how long)
//            -serialize a type that is longer then a byte
//            -deserialize this type again
//            -(E)lectrically (E)rasable (P)rogrammable (R)ead (O)nly (M)emory
//            -read only just means that write is super slow (~ms)

// connect: nothing

class program {
public:
    program() {
        setup();
    }
    void setup() {
        Serial.begin(460800);
        Serial.println("-------------------Start EEPROM program");
        
        //=================== read and write ===================
        
        for(int adr = 0; adr < 5; ++adr) {
            Serial.print("Old value at EEPROM adress ");
            Serial.print(adr);
            Serial.print(" = ");
            Serial.println(int(EEPROM.read(adr))); // adr has to be between 0-1023 / read return a byte
        }
        
        Serial.println("-------------------Starting to write in EEPROM");
        
        for(int adr = 0; adr < 5; ++adr)
            EEPROM.write(adr, 255); //write takes the adress an a byte / this takes long (~ms) / change value to see an effect
        
        for(int adr = 0; adr < 10; ++adr) {
            Serial.print("New value at EEPROM adress ");
            Serial.print(adr);
            Serial.print(" = ");
            Serial.println(int(EEPROM.read(adr)));
        }
        
        //=================== serialize ===================
        // we can only store bytes in EEPROM. Larges types like an uint16_t (2 bytes) need to be serialized
        Serial.println("-------------------serialize example");
        
        uint16_t val = 12345;
        Serial.print("the value to serialized is ");
        Serial.println(val);
        
        EEPROM.write(0, val & 0xFF); //0xFF = 0b11111111 is a mask that kills (set to 0) all but the last byte
        EEPROM.write(1, (val >> 8) & 0xFF); //val>>8 is a bit-shift operator that just shifts the bit 8 times to the right
        
        uint16_t val_from_eeprom = 0;
        
        val_from_eeprom += EEPROM.read(0);
        val_from_eeprom += EEPROM.read(1) << 8; //we need to shift this byte back again
        
        Serial.print("the deserialized value is  ");
        Serial.println(val_from_eeprom);
        
    }

    void loop() {
        //nothing...
    }        
private:
};

#include <main.hpp>
