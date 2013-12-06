// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.11.2013 21:41:50 CET
// File:    tictactoe.hpp

#ifndef __TICTACTOE_HEADER
#define __TICTACTOE_HEADER

#include <Arduino.h>
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>

namespace ttt {
    enum game_enum {
          not_set = 9
        , player = 0
        , ai = 1
        , draw = 2
        , unknown = 9
    };
    
    struct win_type {
        win_type(): p1(0), ai(0), draw(0) {
        }
    //------------------- ops -------------------
        win_type & operator+=(win_type const & rhs) {
            p1 += rhs.p1;
            ai += rhs.ai;
            draw += rhs.draw;
            return (*this);
        }
        bool operator>(win_type const & arg) {
            if((p1 + draw) == 0)
                return true;
            if((arg.p1 + arg.draw) == 0)
                return false;
            if(p1 < arg.p1)
                return true;
            if(p1 == arg.p1 and ai > arg.ai)
                return true;
            if(p1 == arg.p1 and ai == arg.ai and arg.draw > draw)
                return true;
            return false;
        }
    //------------------- members -------------------
        int p1;
        int ai;
        int draw;
    };
    class game_class {
    public:
        game_class(double const & p_random = 0): win_(ttt::unknown), p_random_(p_random) {
            lines_[0][0] = 0;
            lines_[0][1] = 1;
            lines_[0][2] = 2;
            lines_[1][0] = 3;
            lines_[1][1] = 4;
            lines_[1][2] = 5;
            lines_[2][0] = 6;
            lines_[2][1] = 7;
            lines_[2][2] = 8;
            lines_[3][0] = 0;
            lines_[3][1] = 3;
            lines_[3][2] = 6;
            lines_[4][0] = 1;
            lines_[4][1] = 4;
            lines_[4][2] = 7;
            lines_[5][0] = 2;
            lines_[5][1] = 5;
            lines_[5][2] = 8;
            lines_[6][0] = 2;
            lines_[6][1] = 4;
            lines_[6][2] = 6;
            lines_[7][0] = 0;
            lines_[7][1] = 4;
            lines_[7][2] = 8;
            
            reset();
        }
        void reset() {
            for(uint8_t i = 0; i < 9; ++i)
                map_[i] = ttt::not_set;
            
            win_ = ttt::unknown;
        }
    //------------------- ops -------------------
        void player_move(uint8_t const & pos) {
            map_[pos] = ttt::player;
            
            update_win();
        }
        void ai_move() {
            if(free().size() == 9) { //first ai move hardcoded for speed
                map_[random(0, 4)*2 + 1] = ttt::ai;
                update_win();
            }
            else
                ai_recursion();
        }
    private:
        void update_win() {
            for(uint8_t i = 0; i < lines_.size(); ++i) {
                if(map_[lines_[i][0]] == ttt::player and map_[lines_[i][1]] == ttt::player and map_[lines_[i][2]] == ttt::player) {
                    win_ = ttt::player;
                    return;
                }
                if(map_[lines_[i][0]] == ttt::ai and map_[lines_[i][1]] == ttt::ai and map_[lines_[i][2]] == ttt::ai) {
                    win_ = ttt::ai;
                    return;
                }
            }
            if(free().size() == 0)
                win_ = ttt::draw;
        }
        win_type player_recursion() {
            win_type w;
            auto _free = free();
            
            for(uint8_t i = 0; i < _free.size(); ++i) {
                map_[_free[i]] = ttt::player;
                update_win();
                if(win() != ttt::unknown) {
                    w.p1 += (win() == ttt::player);
                    w.draw += (win() == ttt::draw);
                }
                else
                    w += ai_recursion();
                map_[_free[i]] = ttt::not_set;
                win_ = ttt::unknown;
            }
            
            return w;
        }
        win_type ai_recursion() {
            static int depth = 0;
            ++depth;
            auto _free = free();
            ustd::static_vector<win_type, 9> w(_free.size());
            
            for(uint8_t i = 0; i < _free.size(); ++i) {
                map_[_free[i]] = ttt::ai;
                update_win();
                if(win() != ttt::unknown) {
                    w[i].ai = (win() == ttt::ai);
                    w[i].draw = (win() == ttt::draw);
                }
                else
                    w[i] = player_recursion();
                
                map_[_free[i]] = ttt::not_set;
                win_ = ttt::unknown;
            }
            win_type max;
            int max_i = 0;
            max.p1 = 10000;
            for(uint8_t i = 0; i < _free.size(); ++i) {
                if(w[i] > max) {
                    max = w[i];
                    max_i = i;
                }
            }
            if(depth == 1) {
                if(random(100) > p_random_ * 100)
                    map_[_free[max_i]] = ttt::ai;
                else
                    map_[_free[random(_free.size())]] = ttt::ai;
                    
                update_win();
            }
            
            --depth;
            return max;
        }
    public:
    //------------------- getter -------------------
        ustd::static_vector<uint8_t, 9> free() {
            ustd::static_vector<uint8_t, 9> _free;
            for(uint8_t i = 0; i < 9; ++i) {
                if(map_[i] == ttt::not_set)
                    _free.push_back(i);
            }
            return _free;
        }
        uint8_t const & operator[](uint8_t const & idx) const {
            return map_[idx];
        }
        uint8_t const & win() const {
            return win_;
        }
    //------------------- print & serialize -------------------
        template<typename S>
        void print(S & os) const {
            for(uint8_t i = 0; i < 3; ++i) {
                ustd::cout << " ";
                for(uint8_t j = 0; j < 3; ++j) {
                    if(map_[3*i+j] == ttt::player)
                        ustd::cout << GREENB << "O" << NONE;
                    else if(map_[3*i+j] == ttt::ai)
                        ustd::cout << REDB << "X" << NONE;
                    else
                        ustd::cout << " ";
                    
                    if(j < 2)
                        ustd::cout << " | ";
                }
                ustd::cout << ustd::endl;
                if(i < 2)
                    ustd::cout << "---+---+---" << ustd::endl;
            }
        }
    private:
        uint8_t win_;
        ustd::array<uint8_t, 9> map_;
        ustd::array<ustd::array<uint8_t, 3>, 8> lines_;
        double p_random_;
    };
}//end namespace ttt

#endif //__TICTACTOE_HEADER
