// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.11.2013 20:54:55 CET
// File:    tictactoe.cpp

#define COLOR_ON
//~ #define DEBUG_ON
#define ADVANCED_INTERRUPTS

#include <Arduino.h>
#include "tictactoe.hpp"
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>

class program {
public:
    program(): game(0.3) {
        randomSeed(analogRead(A3));
        setup();
    }
    void setup() {
        ustd::cout.init();
        ustd::cout << F("start tictactoe.cpp") << ustd::endl;
        
        music_[ttt::player].set_melody({note::c5, note::f5, note::a5, note::pause}, {1, 1, 1, 2});
        music_[ttt::ai].    set_melody({note::c5, note::c5, note::c5, note::c4}, {1, 1, 1, 2});
        music_[ttt::draw].  set_melody({note::f5, note::f5}, {2, 3});
    }
    void update() {
        tool::clock.update();
    }
    void loop() {
        update();
        
        while(game.win() == ttt::unknown) {
            ustd::static_vector<uint8_t, 9> player_moves = game.free();
            
            ustd::cout << game << ustd::endl;
            ustd::cout << "possible moves: ";
            for(uint8_t i = 0; i < player_moves.size(); ++i) {
                ustd::cout << (int)player_moves[i] << ", ";
            }
            int choice;
            ustd::cin >> choice;
            
            game.player_move(choice);
            
            if(game.win() == ttt::player)
                break;
            
            ustd::cout << game << ustd::endl;
            
            game.ai_move();
        }
        
        ustd::cout << game << ustd::endl;
        ustd::cout << "Win " << game.win() << ustd::endl;
        music_[game.win()].play_blocking();
        
        delay(2000);
        game.reset();
    }
private:
    ttt::game_class game;
    tool::melody_class<D4> music_[4];
};

#include <main.hpp>
