// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    06.12.2013 10:04:36 CET
// File:    tim.hpp

#ifndef __MARIO_HEADER
#define __MARIO_HEADER

#include <Arduino.h>
#include <ustd.hpp>
#include <tool.hpp>
#include <device/PCF8574.hpp>
//  +---------------------------------------------------+
//  |                   constants                       |
//  +---------------------------------------------------+
uint8_t i2c_add = 0;
    
uint8_t const btn1 = 2;
uint8_t const btn2 = 3;
uint8_t const btn3 = 4;

uint8_t const piezo = 5;
bool piezo_down = LOW;
uint8_t const interrupt = 0;

class led_class {
public:
    led_class(device::PCF8574_class & ioexp_):
              led0_(ioexp_)
            , led1_(ioexp_)
            , led2_(ioexp_)
            , led3_(ioexp_)
            , led6_(ioexp_)
            , led7_(ioexp_)
            , led8_(ioexp_)
            , led12_(ioexp_) 
    {}
    void update() {
        led0_.update();
        led1_.update();
        led2_.update();
        led3_.update();
        led4_.update();
        led5_.update();
        led6_.update();
        led7_.update();
        led8_.update();
        led9_.update();
        led10_.update();
        led11_.update();
        led12_.update();
        led13_.update();
        led14_.update();
        led15_.update();
        led16_.update();
        led17_.update();
    }
    void set(uint8_t const & idx, state::light_enum const & state) {
        switch(idx) {
            case(0):
                led0_ = state;
                break;
            case(1):
                led1_ = state;
                break;
            case(2):
                led2_ = state;
                break;
            case(3):
                led3_ = state;
                break;
            case(4):
                led4_ = state;
                break;
            case(5):
                led5_ = state;
                break;
            case(6):
                led6_ = state;
                break;
            case(7):
                led7_ = state;
                break;
            case(8):
                led8_ = state;
                break;
            case(9):
                led9_ = state;
                break;
            case(10):
                led10_ = state;
                break;
            case(11):
                led11_ = state;
                break;
            case(12):
                led12_ = state;
                break;
            case(13):
                led13_ = state;
                break;
            case(14):
                led14_ = state;
                break;
            case(15):
                led15_ = state;
                break;
            case(16):
                led16_ = state;
                break;
            case(17):
                led17_ = state;
                break;
        }
    }
private:
    //------------------- hardware -------------------
    tool::light_class<tool::PCF8574<4>, LOW> led0_;
    tool::light_class<tool::PCF8574<5>, LOW> led1_;
    tool::light_class<tool::PCF8574<6>, LOW> led2_;
    tool::light_class<tool::PCF8574<7>, LOW> led3_;
    tool::light_class<D11, LOW> led4_;
    tool::light_class<D8, LOW> led5_;

    tool::light_class<tool::PCF8574<1>, LOW> led6_;
    tool::light_class<tool::PCF8574<2>, LOW> led7_;
    tool::light_class<tool::PCF8574<3>, LOW> led8_;
    tool::light_class<D12, LOW> led9_;
    tool::light_class<D10, LOW> led10_;
    tool::light_class<D7, LOW> led11_;

    tool::light_class<tool::PCF8574<0>, LOW> led12_;
    tool::light_class<DA1, LOW> led13_;
    tool::light_class<DA0, LOW> led14_;
    tool::light_class<D13, LOW> led15_;
    tool::light_class<D9, LOW> led16_;
    tool::light_class<D6, LOW> led17_;
};


#endif //__MARIO_HEADER
