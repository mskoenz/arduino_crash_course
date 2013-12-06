// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.11.2013 20:54:55 CET
// File:    tictactoe.cpp

#define COLOR_ON
//~ #define DEBUG_ON
#define ADVANCED_INTERRUPTS

#include <Arduino.h>
#include <ustd.hpp>
#include "tictactoe.hpp"

class program {
public:
    program(): game(0.2) {
        randomSeed(analogRead(A3));
        setup();
    }
    void setup() {
        ustd::cout.init();
        ustd::cout << F("start tictactoe.cpp") << ustd::endl;
        using namespace note;
        music_[ttt::player].set_melody({c4, c5, c6, c3}, {1, 1, 1, 1});
        music_[ttt::player].set_unit_dur(200);
        //~ music_[ttt::ai]
        //~ music_[ttt::draw]
        
        music_[ttt::player].play();
        music_[ttt::player].repeat(true);
    }
    void update() {
        tool::clock.update();
        music_[ttt::player].update();
        
        
    }
    void loop() {
        update();
        
        //~ while(game.win() == ttt::unknown) {
            //~ ustd::cout << game << ustd::endl;
            //~ 
            //~ ustd::cout << F("possible moves: ");
            //~ auto free = game.free();
            //~ ustd::cout << free << ustd::endl;
            //~ 
            //~ uint8_t choice;
            //~ 
            //~ ustd::cin >> choice;
            //~ //player is nice
            //~ 
            //~ game.player_move(choice);
            //~ 
            //~ ustd::cout << game << ustd::endl;
            //~ 
            //~ if(game.win() == ttt::unknown)
                //~ game.ai_move();
        //~ }
        //~ 
        //~ ustd::cout << "Winner: " << game.win() << ustd::endl;
        //~ music_[game.win()];
        //~ game.reset();
        
    }
private:
    ttt::game_class game;
    tool::melody_class<D4> music_[3];
};

#include <main.hpp>
