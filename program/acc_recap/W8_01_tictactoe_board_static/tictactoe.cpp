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
            , game(0.3) //chance of making a random move instead of the optimal
            , last_key_(0) {
        
        randomSeed(0); //doesn't matter since the device is always on and never resetted
        setup();
    }
    void setup() {
        ustd::cout.init(); //only for debugging
        com::i2c_begin();
        ioexp_.write(0xFF); //turn all lights off on the PCF
    
    //------------------- define music for victorys -------------------
        pinMode(piezo, INPUT); //important. We dont want some currents to flow. tone ignores this anyway
        digitalWrite(piezo, piezo_down); //the piezo uses up to 60 ma if the potential is not equal on both ends
        
        music_[ttt::player].set_melody({note::c5, note::f5, note::a5, note::c6}, {1, 1, 1, 2});
        music_[ttt::ai].    set_melody({note::c5, note::c5, note::c5, note::c4}, {1, 1, 1, 2});
        music_[ttt::draw].  set_melody({note::f5, note::f5}, {2, 3});
    
    //------------------- init game -------------------
        free_ = game.free();
        choice_ = 0;
        //0,2,4... are the red leds and 1,3,5... are the green leds -> 2*i+1
        led_.set(2*free_[choice_]+1, state::fast); //switch on the selection led
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
        
        if(btn1_ == state::falling) { //move selection
            last_key_ = tool::clock.millis(); //reset sleep-timer
            noise(note::c4, 100);
            
            led_.set(2*free_[choice_]+1, state::off); //turn off current selection
            
            if(choice_ == 0) //check bounds
                choice_ = free_.size() - 1;
            else
                --choice_;
            
            led_.set(2*free_[choice_]+1, state::fast); //turn on new selection
        }
        if(btn3_ == state::falling) { //move selection
            last_key_ = tool::clock.millis(); //reset sleep-timer
            noise(note::d4, 100);
            
            
            led_.set(2*free_[choice_]+1, state::off); //turn off current selection
            
            if(choice_ == free_.size() - 1) //check bounds
                choice_ = 0;
            else
                ++choice_;
                
            led_.set(2*free_[choice_]+1, state::fast); //turn on new selection
        }
        if(btn2_ == state::falling) { //confirm selection
            last_key_ = tool::clock.millis(); //reset sleep-timer
            noise(note::c5, 100);
            
            led_.set(2*free_[choice_]+1, state::on); //turn on current selection
            update(); //to see the lights, since we don't reach the update() fct until after the ai did the move
            
            game.player_move(free_[choice_]);
            
            
            
            if(game.win() == ttt::unknown) { //only let ai play if game is not over yet
                noise(note::c6, 100);
                game.ai_move();
                for(uint8_t i = 0; i < 9; ++i) { //go through all fileds and turn on ai-lights
                    if(game[i] == ttt::ai)
                        led_.set(2*i, state::on);
                }
                update(); //again, to see the lights
            }
            
            
            if(game.win() == ttt::unknown) { //only light up the selection if game is still on
                free_ = game.free();
                choice_ = 0;
                led_.set(2*free_[choice_]+1, state::fast);
            }
        }
        if(game.win() != ttt::unknown) { //game is over
            music_[game.win()].play_blocking(); //victory theme
            game.reset();
            
            for(uint8_t i = 0; i < 18; ++i) { //turn off entire board
                led_.set(i, state::off);
            }
            //create the selection again
            free_ = game.free();
            choice_ = 0;
            led_.set(2*free_[choice_]+1, state::fast);
        }
        //------------------- timeout -------------------
        if(tool::clock.millis() - last_key_ > 20000) {
            last_key_ = tool::clock.millis();
            
            for(uint8_t i = 0; i < 18; ++i) { //trun off all lights
                led_.set(i, state::off);
            }
            update(); //actually does this
            
            noise(note::c3, 500);
            
            util::sleep(interrupt);
            
            noise(note::c6, 500);
            for(uint8_t i = 0; i < 9; ++i) { //if back, light up the board according to the state
                if(game[i] == ttt::player)
                    led_.set(2*i + 1, state::on);
                if(game[i] == ttt::ai)
                    led_.set(2*i, state::on);
            }
            update();
            led_.set(2*free_[choice_]+1, state::fast); //and the selection
        }
    }
    void noise(int const & note, int const & dur) {
        tone(piezo, note, dur);
        delay(dur-10); //-10 for clearer cuts
        noTone(piezo);
        digitalWrite(piezo, piezo_down); //saves tons of energy
    }
    void receive(int n) {} //have to be here for the i2c module (I will change this soon)
    void request() {} //have to be here for the i2c module (I will change this soon)
private:
    device::PCF8574_class ioexp_; //the expander
    led_class led_; //all 18 leds
    tool::button_class<tool::intern<btn1>, LOW> btn1_;
    tool::button_class<tool::intern<btn2>, LOW> btn2_;
    tool::button_class<tool::intern<btn3>, LOW> btn3_;

//------------------- software -------------------
    uint8_t choice_;
    ustd::static_vector<uint8_t, 9> free_;
    ttt::game_class game;
    tool::melody_class<tool::intern<piezo>> music_[3];
    
    double last_key_; //for the sleep-timeout
};

#include <main.hpp>
