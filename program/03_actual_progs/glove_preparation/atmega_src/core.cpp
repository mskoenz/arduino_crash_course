// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.07.2013 16:40:55 EDT
// File:    glove_prep.cpp

#define COLOR_ON
#define DEBUG_ON
#define ADVANCED_INTERRUPTS

#include <util/fast_io.hpp>
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>
#include <com/i2c.hpp>
#include <com/eeprom.hpp>
#include <com/uart.hpp>

#include "bridge.hpp"
#include "hardware_constants.hpp"
#include "position.hpp"
#include "learn.hpp"

#include "core_protocol.hpp"

char in;

class program {
public:
    program() {
        setup();
    }
    void setup() {
        ustd::cout.init(core::speed);
        com::i2c_begin(core::i2c_adress);
        red_ = state::off;
        blue_ = state::off;
        green_ = state::flash;
        
        
        //~ com::eeprom.clear();
        com::eeprom & gest_;
    }
    void update() {
        tool::clock.update();
        red_.update();
        blue_.update();
        green_.update();
        btn_.update();
        pos_.update();
        
        for(uint8_t i = 0; i < core::max_gest; ++i) {
            curr_gest_ = 0xFF;
            if(gest_[i].contains(pos_.pos())) {
                curr_gest_ = gest_[i].id();
                break;
            }
        }
    }
    void loop() {
        update();
        
        green_ = 0;
        blue_ = 0;
        red_ = 0;
        if(curr_gest_ != 0xFF)
            red_ = 1;
        else
            blue_ = state::fast;
        
        if(btn_)
            learn_.set_iter(5);
        
        if(learn_) {
            
            ustd::accumulator<uint8_t, ustd::tag::min, ustd::tag::max> acc[9];
            
            for(learn_.cur_iter = 0; learn_.cur_iter < learn_.max_iter(); ++learn_.cur_iter) {
                green_ = 0;
                blue_ = 0;
                red_ = 1;
                
                for(uint8_t i = 0; i < 250; ++i) {
                    update();
                    delay(4);
                }
                
                red_ = 0;
                blue_  = 1;
                while(pos_.change() > 200) {
                    update();
                    delay(1);
                }
                blue_ = 0;
                
                for(uint8_t i = 0; i < 9; ++i) {
                    acc[i] << (uint8_t)pos_[i];
                }
                
                green_ = 1;
                while(pos_.change() > 4) {
                    update();
                    delay(5);
                }
                green_ = 0;
                
                for(uint8_t i = 0; i < 9; ++i) {
                    acc[i] << (uint8_t)pos_[i];
                }
            }
            learn_.set_iter(0);
            
            gest_.push_back(gesture_class());
            
            for(uint8_t i = 0; i < 9; ++i) {
                gest_.back().low()[i] = acc[i].min();
                gest_.back().high()[i] = acc[i].max();
            }
        }
        
        
        if(com::uart) {
            in = 0;
            com::uart >> in;
            ustd::cout << in << ustd::endl;
            if(in == core::raw_value) {
                ustd::cout << pos_;
            } else if(in == core::read_n_gestures) {
                ustd::cout << gest_.size();
            } else if(in == core::current_gesture) {
                ustd::cout << curr_gest_;
            }
            ustd::cout << ustd::endl;
            while(Serial.available())
                Serial.read();
        }
        
        //~ ustd::cout << pos_ << ustd::endl;
        //~ diag::speed_report();
    }
    void receive(int n) {
        com::i2cin >> in;
        
        if(in == core::raw_value) {
            com::i2cout << pos_;
        } else if(in == core::read_gesture) { //means write on this end
            com::i2cin >> in;
            com::i2cout << gest_[in];
        } else if(in == core::write_gesture) { //means read on this end
            com::i2cin >> in;
            com::i2cin >> gest_[in];
        } else if(in == core::read_n_gestures) {
            in = gest_.size();
            com::i2cout << in;
        } else if(in == core::write_n_gestures) {
            com::i2cin >> in;
            gest_.set_size(in);
        } else if(in == core::write_to_eeprom) {
            com::eeprom << gest_;
        } else if(in == core::remove_all_gestures) {
            gest_.clear();
        } else if(in == core::current_gesture) {
            com::i2cout << curr_gest_;
        }
        
        //~ if(in == 'r') {
            //~ com::i2cout << gest_[0];
        //~ }
        //~ if(in == 's') {
        //~ }
        //~ if(in == 'l') {
            //~ if(n > 1) {
                //~ com::i2cin >> in;
                //~ learn_.set_iter(in);
            //~ }
            //~ else
                //~ learn_.set_iter(0xFF); //255 iteration = infinity
        //~ }
    }
    void request() {
        com::i2cout << ustd::endl;
    }
private:
    tool::light_class<tool::intern<RED_LED>, LOW> red_;
    tool::light_class<tool::intern<BLUE_LED>, LOW> blue_;
    tool::light_class<tool::intern<GREEN_LED>, LOW> green_;
    //VERSION: 2 HIGH, 3 LOW
    tool::button_class<tool::intern<BUTTON>, LOW> btn_;
    
    position_class pos_;
    ustd::static_vector<gesture_class, core::max_gest> gest_;
    learn_algo_class learn_;
    uint8_t curr_gest_;
};

#include <main.hpp>
