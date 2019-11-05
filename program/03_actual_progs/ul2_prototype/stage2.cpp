// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    21.09.2013 21:13:51 CEST
// File:    stage2.cpp

#define COLOR_ON
//~ #define DEBUG_ON
#define ADVANCED_INTERRUPTS

#include <util/fast_io.hpp>
#include <Arduino.h>
#include <ustd.hpp>
#include <diag.hpp>
#include <tool.hpp>

#include <numerics.hpp>

#include <com/i2c.hpp>
#include <LiquidCrystal.h>
#include <com/adv_eeprom.hpp>
#include <device/usb_hid.hpp>
#include <device/MCP4561.hpp>
#include <device/24LC256.hpp>

#include "keys_n_chars.hpp"

#define STATUS(x) lcd_.setCursor(15, 0); lcd_.print(x);

namespace glob {
    
    uint8_t const n_keys = 27;
    uint8_t const n_profiles = 30;
    uint8_t const n_tiers = 3;
    uint8_t const n_name = 9;
    
    uint8_t const red = 0;
    uint8_t const green = 1;
    uint8_t const blue = 2;
    
    //led bounds
    uint8_t const max_col = 5;
    uint8_t const max_power = 50;
    
    //shutter bounds
    uint8_t const mcp_high = 255;
    uint8_t const mcp_low  = 205;
    
    //apm menu
    uint8_t const mean_1 = 60;
    uint8_t const mean_2 = 5;
    
}//end namespace glob

typedef ustd::array<uint8_t, 3> color_type;

class led_class {
public:
    led_class(): high_power(50), low_power(1) {
    }
    void update() {
        red_.update();
        blue_.update();
        green_.update();
    }
    void high(color_type const & col) {
        red_ = col[glob::red] * high_power;
        green_ = col[glob::green] * high_power;
        blue_ = col[glob::blue] * high_power;
    }
    void low(color_type const & col) {
        red_ = col[glob::red] * low_power;
        green_ = col[glob::green] * low_power;
        blue_ = col[glob::blue] * low_power;
    }
    
    uint8_t high_power;
    uint8_t low_power;
private:
    tool::light_class<9, LOW> red_;
    tool::light_class<11, LOW> blue_;
    tool::light_class<10, LOW> green_;
};

struct profile_struct {
    profile_struct() {
        set_name("not set ");
        tier = 0;
        for(uint8_t i = 0; i < glob::n_keys; ++i) {
            _key[0][i] = 0;
            _mod[0][i] = 0;
        }
        color[glob::red] = 0;
        color[glob::green] = 4;
        color[glob::blue] = 0;
    }
    void set_name(ustd::string c) {
        for(uint8_t i = 0; i < glob::n_name; ++i) {
            name[i] = c[i];
        }
    }
//------------------- getters -------------------
    uint8_t & key(uint8_t const & pos) {
        return _key[tier][pos];
    }
    uint8_t & mod(uint8_t const & pos) {
        return _mod[tier][pos];
    }
//------------------- serialize -------------------
    template<typename Archive>
    void serialize(Archive & ar) {
        ar & tier;
        ar & _key;
        ar & _mod;
        ar & color;
        ar & name;
    }
    uint8_t tier;
    ustd::array<ustd::array<uint8_t, glob::n_keys>, glob::n_tiers> _key;
    ustd::array<ustd::array<uint8_t, glob::n_keys>, glob::n_tiers> _mod;
    color_type color;
    ustd::array<char, glob::n_name> name;
};

class program {
public:
    program():    menu_button_(26)
                , lcd_(12, 13, A0, A1, A2, A3)
                , shutter_val_(235)
                , lcd_led_val_(250)
                , eeprom_(eeprom_in_)
    {
        
        setup();
    }
    void setup() {
        ustd::cout.init(19200);
        ustd::cout << F("start stage2.cpp") << ustd::endl;
        
        com::i2c_begin();
        //~ for(uint16_t i = 0; i < 6000; ++i) {
            //~ ustd::cout << eeprom_in_.read(i) << " ";
        //~ }
        //~ ustd::cout << F("done") << ustd::endl;
        
        lcd_.begin(16, 2);
        lcd_.print(F("    UPLINK V2"));
        lcd_.setCursor(0, 1);
        lcd_.print(F("      init   "));
        
        lcd_.createChar(glob::up, up);
        lcd_.createChar(glob::down, down);
        lcd_.createChar(glob::on, on);
        lcd_.createChar(glob::shift, shift);
        lcd_.createChar(glob::gui, gui);
        lcd_.createChar(glob::alt, alt_custom);
        lcd_.createChar(glob::ctrl, ctrl);
        
        //~ eeprom_.reset();
        //~ ustd::cout << F("reset") << ustd::endl;
        //~ demo_settings();
        
        eeprom_ & active_profile_;
        eeprom_ & com::version(glob::n_profiles) & profile_;
        eeprom_ & menu_button_;
        
        eeprom_ & shutter_val_;
        eeprom_ & lcd_led_val_;
        eeprom_ & led_.high_power;
        eeprom_ & led_.low_power;
        
        init_menu_methods();
        
        lcd_led_ = lcd_led_val_;
        mcp_ = shutter_val_;
        
        //~ init_EEPROM();
        //~ ustd::cout << F("init") << ustd::endl;
        
        //~ demo_settings();
        //~ eeprom_ << com::version(0) << profile_;
        //~ ustd::cout << F("demo") << ustd::endl;
        
        eeprom_ >> com::version(active_profile_) >> profile_;
        
        usb_.connect();
        
        init_disp();
        //~ diag::ram_report();
    }
//=================== special settings ===================
    void init_EEPROM() {
        profile_ = profile_struct();
        active_profile_ = 0;
        for(uint8_t i = 0; i < glob::n_profiles; ++i)
            eeprom_ << com::version(i) << profile_;
    }
    void demo_settings() {
        lcd_led_val_ = 250;
        shutter_val_ = 235;
        led_.high_power = 50;
        led_.low_power = 1;
        
        profile_.color[glob::red] = 2;
        profile_.color[glob::blue] = 4;
        profile_.color[glob::green] = 0;

        profile_.set_name("  demo  ");
        for(uint8_t i = 0; i < glob::n_keys; ++i) {
            for(uint8_t k = 0; k < glob::n_tiers; ++k) {
                profile_.tier = k;
                profile_.key(i) = (uint8_t)key::a + k;
                if(i == menu_button_)
                    profile_.mod(i) = (uint8_t)key::none;
                else
                    profile_.mod(i) = (uint8_t)key::shift;
            }
            profile_.tier = 0;
        }
    }
//  +---------------------------------------------------+
//  |                   global update/loop              |
//  +---------------------------------------------------+
    void update() {
        com::i2cin(66) >> ar_;
        com::i2cin(66) >> tool::clock;
        usb_.delay_ms(2);
        
        lcd_led_.update();
        led_.update();
    }
    void loop() {
        update();
        
        if(ar_[menu_button_] & state::falling) {
            usb_.release_all();
            hid_update();
            menu_loop();
            init_disp();
        }
        else
            hid_loop();
        
    }
//  +---------------------------------------------------+
//  |                   usb update/loop                 |
//  +---------------------------------------------------+
    void hid_update() {
        usb_.update();
        //------------------- key highlight -------------------
        if(usb_.any_pressed()) {
            led_.high(profile_.color);
        } else {
            led_.low(profile_.color);
        }
    }
    ustd::static_vector<uint8_t, 3> list;
    void hid_loop() {
        hid_update();
        
        for(uint8_t i = 0; i < glob::n_keys; ++i) {
            if(ar_[i] & state::falling) {
                if(profile_.key(i) < glob::tier[0]) {
                    if(list.size() == list.capacity()) {
                        list.erase(0);
                    }
                    list.push_back(i);
                    usb_.press(profile_.key(i), profile_.mod(i));
                }
                else {
                    usb_.release_all();
                    profile_.tier = profile_.key(i) - glob::tier[0];
                    for(uint8_t k = 0; k < list.size(); ++k) {
                        usb_.press(profile_.key(list[k]), profile_.mod(list[k]));
                    }
                }
            }
            else if(ar_[i] & state::raising) {
                if(profile_.key(i) < glob::tier[0]) {
                    list.erase(list.find(i));
                    usb_.release(profile_.key(i), profile_.mod(i));
                }
                else {
                    usb_.release_all();
                    profile_.tier = profile_.key(i) - glob::tier[0];
                    for(uint8_t k = 0; k < list.size(); ++k) {
                        usb_.press(profile_.key(list[k]), profile_.mod(list[k]));
                    }
                }
            }
        }
        (this->*disp_fct)(); //update display
    }
//  +---------------------------------------------------+
//  |                   menu update/loop                |
//  +---------------------------------------------------+
    void menu_update() {
        update();
        //------------------- key highlight -------------------
        if(accumulate(ar_) > glob::n_keys) {
            led_.high(profile_.color);
        } else {
            led_.low(profile_.color);
        }
    }
    void menu_loop() {
        fct = &program::main_menu;
        status = 1;
        
        while(status) {
            menu_update();
            (this->*fct)();
        }
    }
//=================== main menus ===================
    #include "menu_methods.hpp"
//=================== i2c ===================
    void receive(int n) {}
    void request() {}
private:
    uint8_t menu_button_;
    
    uint8_t active_profile_;
    profile_struct profile_;
    
    ustd::array<uint8_t, glob::n_keys> ar_;
//------------------- LCD -------------------
    LiquidCrystal lcd_;
    tool::light_class<3, HIGH> lcd_led_;
//------------------- Digi Pot -------------------
    device::MCP4561_class mcp_;
    uint8_t shutter_val_;
    uint8_t lcd_led_val_;
//------------------- USB-HID -------------------
    device::usb_hid_class usb_;
//------------------- EEPROM -------------------
    device::_24LC256_class eeprom_in_;
    com::EEPROMV2_class<device::_24LC256_class, 1024*64l-1> eeprom_;
//------------------- Tricolor LED -------------------
    led_class led_;
};

#include <main.hpp>
