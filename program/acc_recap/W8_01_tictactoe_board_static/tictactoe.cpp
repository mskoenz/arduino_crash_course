// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.11.2013 20:54:55 CET
// File:    tictactoe.cpp

//~ #define COLOR_ON
//~ #define DEBUG_ON
//~ #define ADVANCED_INTERRUPTS

#include <Arduino.h>
#include "tictactoe.hpp"
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>
#include <device/PCF8574.hpp>
#include <util/sleep.hpp>

//~ #include <mario.hpp>
//~ #include <dominik.hpp>
//~ #include <rico.hpp>
//~ #include <donjan.hpp>
//~ #include <cyrill.hpp>
//~ #include <tim.hpp>
//~ #include <andreas.hpp>
//  +---------------------------------------------------+
//  |                   program                         |
//  +---------------------------------------------------+
class program {
public:
    program(): ioexp_(i2c_add)
            , led_(ioexp_)
            , game(0.3)
            , last_key_(0) {
        
        randomSeed(analogRead(A3));
        setup();
    }
    void setup() {
        ustd::cout.init();
        com::i2c_begin();
        ioexp_.write(0xFF);
    //------------------- define music for victory -------------------
        pinMode(piezo, INPUT);
        digitalWrite(piezo, piezo_down);
        music_[ttt::player].set_melody({note::c5, note::f5, note::a5, note::c6}, {1, 1, 1, 2});
        music_[ttt::ai].    set_melody({note::c5, note::c5, note::c5, note::c4}, {1, 1, 1, 2});
        music_[ttt::draw].  set_melody({note::f5, note::f5}, {2, 3});
    //------------------- init game -------------------
        free_ = game.free();
        choice_ = 0;
        led_.set(2*free_[choice_]+1, state::fast);
    }
    void update() {
        tool::clock.update();
        btn1_.update();
        btn2_.update();
        btn3_.update();
        
        led_.update();
    }
    void loop() {
        update();
        
        if(btn1_ == state::falling) {
            last_key_ = tool::clock.millis();
            noise(note::c4, 100);
            
            led_.set(2*free_[choice_]+1, state::off);
            
            if(choice_ == 0)
                choice_ = free_.size() - 1;
            else
                --choice_;
            
            led_.set(2*free_[choice_]+1, state::fast);
        }
        if(btn3_ == state::falling) {
            last_key_ = tool::clock.millis();
            noise(note::d4, 100);
            
            
            led_.set(2*free_[choice_]+1, state::off);
            
            if(choice_ == free_.size() - 1)
                choice_ = 0;
            else
                ++choice_;
                
            led_.set(2*free_[choice_]+1, state::fast);
        }
        if(btn2_ == state::falling) {
            last_key_ = tool::clock.millis();
            noise(note::c5, 100);
            
            led_.set(2*free_[choice_]+1, state::off);
            
            game.player_move(free_[choice_]);
            
            for(uint8_t i = 0; i < 9; ++i) {
                if(game[i] == ttt::player)
                    led_.set(2*i + 1, state::on);
            }
            update(); //to see the lights
            
            if(game.win() == ttt::unknown) {
                game.ai_move();
                noise(note::c6, 100);
                for(uint8_t i = 0; i < 9; ++i) {
                    if(game[i] == ttt::ai)
                        led_.set(2*i, state::on);
                }
                update(); //to see the lights
            }
            
            
            if(game.win() == ttt::unknown) {
                free_ = game.free();
                choice_ = 0;
                led_.set(2*free_[choice_]+1, state::fast);
            }
        }
        if(game.win() != ttt::unknown) {
            music_[game.win()].play_blocking();
            game.reset();
            
            for(uint8_t i = 0; i < 18; ++i) {
                led_.set(i, state::off);
            }
            
            free_ = game.free();
            choice_ = 0;
            led_.set(2*free_[choice_]+1, state::fast);
        }
        //------------------- timeout -------------------
        if(tool::clock.millis() - last_key_ > 20000) {
            last_key_ = tool::clock.millis();
            
            for(uint8_t i = 0; i < 18; ++i) {
                led_.set(i, state::off);
            }
            update();
            
            noise(note::c3, 500);
            
            util::sleep(interrupt);
            
            for(uint8_t i = 0; i < 9; ++i) {
                if(game[i] == ttt::player)
                    led_.set(2*i + 1, state::on);
                if(game[i] == ttt::ai)
                    led_.set(2*i, state::on);
            }
            update();
            led_.set(2*free_[choice_]+1, state::fast);
            noise(note::c6, 500);
        }
    }
    void noise(int const & note, int const & dur) {
        tone(piezo, note, dur);
        delay(dur-10);
        noTone(piezo);
        digitalWrite(piezo, piezo_down);
    }
    void receive(int n) {}
    void request() {}
private:
    device::PCF8574_class ioexp_;
    led_class led_;
    tool::button_class<tool::intern<btn1>, LOW> btn1_;
    tool::button_class<tool::intern<btn2>, LOW> btn2_;
    tool::button_class<tool::intern<btn3>, LOW> btn3_;

//------------------- software -------------------
    uint8_t choice_;
    ustd::static_vector<uint8_t, 9> free_;
    ttt::game_class game;
    tool::melody_class<tool::intern<piezo>> music_[3];
    
    double last_key_;
};

#include <main.hpp>
