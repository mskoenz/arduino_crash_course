// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.11.2013 20:54:55 CET
// File:    tictactoe.cpp

//~ #define COLOR_ON
//~ #define DEBUG_ON
//~ #define ADVANCED_INTERRUPTS

#include <util/fast_io.hpp>
#include <Arduino.h>
#include "tictactoe.hpp"
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>
#include <util.hpp>
#include <device/PCF8574.hpp>

//  +---------------------------------------------------+
//  |                   constants                       |
//  +---------------------------------------------------+
uint8_t i2c_add = 0;
    
uint8_t const btn1 = 2;
uint8_t const btn2 = 3;
uint8_t const btn3 = 4;

uint8_t const piezo = 10;

//  +---------------------------------------------------+
//  |                   program                         |
//  +---------------------------------------------------+
class program {
public:
    program(): ioexp_(i2c_add), game(0.15), last_key_(0) {
        randomSeed(analogRead(A3));
        setup();
    }
    void setup() {
        ustd::cout.init();
        ustd::cout << F("start tictactoe.cpp") << ustd::endl;
        com::i2c_begin();
        ioexp_.write(0xFF);
        
    //------------------- define music for victory -------------------
        music_[ttt::player].set_melody({note::c5, note::f5, note::a5, note::c6}, {1, 1, 1, 2});
        music_[ttt::ai].    set_melody({note::c5, note::c5, note::c5, note::c4}, {1, 1, 1, 2});
        music_[ttt::draw].  set_melody({note::f5, note::f5}, {2, 3});
        
    //------------------- init vector -------------------
        delay(100);
        led_.reserve(18);
        
        led_.push_back(tool::light_class<tool::PCF8574<5>, LOW>(ioexp_));
        led_.push_back(tool::light_class<tool::PCF8574<4>, LOW>(ioexp_));
        led_.push_back(tool::light_class<tool::PCF8574<3>, LOW>(ioexp_));
        led_.push_back(tool::light_class<D12, LOW>());
        led_.push_back(tool::light_class<D11, LOW>());
        led_.push_back(tool::light_class<D6, LOW>());
        
        led_.push_back(tool::light_class<tool::PCF8574<7>, LOW>(ioexp_));
        led_.push_back(tool::light_class<tool::PCF8574<6>, LOW>(ioexp_));
        led_.push_back(tool::light_class<tool::PCF8574<2>, LOW>(ioexp_));
        led_.push_back(tool::light_class<D13, LOW>());
        led_.push_back(tool::light_class<D9, LOW>());
        led_.push_back(tool::light_class<D7, LOW>());
        
        led_.push_back(tool::light_class<DA1, LOW>());
        led_.push_back(tool::light_class<DA2, LOW>());
        led_.push_back(tool::light_class<tool::PCF8574<1>, LOW>(ioexp_));
        led_.push_back(tool::light_class<tool::PCF8574<0>, LOW>(ioexp_));
        led_.push_back(tool::light_class<D8, LOW>());
        led_.push_back(tool::light_class<D5, LOW>());
    //------------------- init game -------------------
        free_ = game.free();
        choice_ = 0;
        led_[2*free_[choice_]+1] = state::fast;
    }
    void update() {
        tool::clock.update();
        btn1_.update();
        btn2_.update();
        btn3_.update();
        
        for(uint8_t i = 0; i < led_.size(); ++i) {
            led_[i].update();
        }
    }
    void loop() {
        update();
        
        if(btn1_ == state::falling) {
            last_key_ = tool::clock.millis();
            
            noise(note::c4, 50);
            led_[2*free_[choice_]+1] = state::off;
            
            if(choice_ == 0)
                choice_ = free_.size() - 1;
            else
                --choice_;
            
            led_[2*free_[choice_]+1] = state::fast;
        }
        if(btn3_ == state::falling) {
            last_key_ = tool::clock.millis();
            
            noise(note::d4, 50);
            
            led_[2*free_[choice_]+1] = state::off;
            
            if(choice_ == free_.size() - 1)
                choice_ = 0;
            else
                ++choice_;
            
            led_[2*free_[choice_]+1] = state::fast;
        }
        if(btn2_ == state::falling) {
            last_key_ = tool::clock.millis();
            
            noise(note::c5, 100);
            
            game.player_move(free_[choice_]);
            
            led_[2*free_[choice_]+1] = state::on;
            update(); //to see the light
            
            if(game.win() == ttt::unknown) {
                game.ai_move();
                for(uint8_t i = 0; i < 9; ++i) {
                    if(game[i] == ttt::ai)
                        led_[2*i] = state::on;
                }
                update(); //to see the light
                noise(note::c4, 100);
            }
            
            
            if(game.win() == ttt::unknown) {
                free_ = game.free();
                choice_ = 0;
                led_[2*free_[choice_]+1] = state::fast;
            }
        }
    //------------------- victory and reset -------------------
        if(game.win() != ttt::unknown) {
            last_key_ = tool::clock.millis();
            
            music_[game.win()].play_blocking();
            digitalWrite(piezo, HIGH);
            
            game.reset();
            
            for(uint8_t i = 0; i < 18; ++i) {
                led_[i] = state::off;
            }
            
            free_ = game.free();
            choice_ = 0;
            led_[2*free_[choice_]+1] = state::fast;
        }
    //------------------- timeout -------------------
        if(tool::clock.millis() - last_key_ > 20000) {
            last_key_ = tool::clock.millis();
            
            for(uint8_t i = 0; i < led_.size(); ++i) {
                led_[i] = state::off;
            }
            update();
            
            noise(note::c3, 500);
            
            util::sleep(0);
            
            for(uint8_t i = 0; i < 9; ++i) {
                if(game[i] == ttt::player)
                    led_[2*i + 1] = state::on;
                if(game[i] == ttt::ai)
                    led_[2*i] = state::on;
            }
            update();
            led_[2*free_[choice_]+1] = state::fast;
            noise(note::c6, 500);
        }
    }
    void noise(int const & note, int const & dur) {
        tone(piezo, note, dur);
        delay(dur-10);
        noTone(piezo);
        digitalWrite(piezo, HIGH);
    }
    void receive(int n) {}
    void request() {}
private:
//------------------- hardware -------------------
    device::PCF8574_class ioexp_;
    tool::button_class<tool::intern<btn1>, LOW> btn1_;
    tool::button_class<tool::intern<btn2>, LOW> btn2_;
    tool::button_class<tool::intern<btn3>, LOW> btn3_;
    ustd::vector<tool::light_wrapper_class> led_;

//------------------- software -------------------
    uint8_t choice_;
    ustd::static_vector<uint8_t, 9> free_;
    ttt::game_class game;
    tool::melody_class<tool::intern<piezo>> music_[3];
    
    double last_key_;
};

#include <main.hpp>
