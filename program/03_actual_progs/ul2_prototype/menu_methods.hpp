// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.09.2013 23:28:34 CEST
// File:    menu_methods.hpp

#ifndef __MENU_METHODS_HEADER
#define __MENU_METHODS_HEADER

uint8_t status;
void(program::*fct)(void);
uint8_t disp_modus;
void(program::*disp_fct)(void);

enum key_mapping {
      next_main = 4
    , ok = 23
    , abort = 22
    , prev_main = 5
    , next_sub = 1
    , prev_sub = 0
    , incr_one = next_main
    , decr_one = prev_main
    , incr_two = 2
    , decr_two = 3
};

void init_menu_methods() {
    eeprom_ & disp_modus;
    
    switch(disp_modus) {
        case(0):
            disp_fct = &program::time_menu;
            break;
        case(1):
            disp_fct = &program::disp_key_menu;
            break;
        case(2):
            disp_fct = &program::apm_menu;
            break;
        case(3):
            disp_fct = &program::dark_menu;
            break;
        default:
            disp_fct = &program::time_menu;
            disp_modus = 0;
            eeprom_ << disp_modus;
    }
    
}
void init_disp() {
    lcd_.clear();
    status = 4;
    (this->*disp_fct)();
    status = 0;
}
void goto_menu(void(program::*_fct)(void), uint8_t const & key) {
    if(ar_[key] & state::falling) {
        fct = _fct;
        status = 1;
    }
}
//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
void main_menu() {
    if(status == 1) {
        lcd_.begin(16, 2);
        lcd_led_ = lcd_led_val_; //bc dark_menu
        lcd_.print(F("   main menu"));
        status = 2;
    }
    
    goto_menu(&program::profile_menu, next_main);
    goto_menu(&program::key_menu, prev_main);
    if((ar_[menu_button_] & state::falling) or (ar_[next_sub] & state::falling)) {
        status = 0;
    }
}
//  +---------------------------------------------------+
//  |                   profile                         |
//  +---------------------------------------------------+
uint8_t cursor_pos;
uint8_t cursor_pos_2;
void profile_menu() {
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("  profile menu"));
        status = 2;
    }
    
    goto_menu(&program::display_menu, next_main);
    goto_menu(&program::main_menu, prev_main);
    goto_menu(&program::change_profile_menu, next_sub);
    
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
}
void change_profile_menu() {
    auto prt = [&](){
        lcd_.setCursor(1, 1);
        lcd_.print(int(active_profile_) + 1);
        lcd_.print(F(": "));
        lcd_.print(profile_.name.data());
        lcd_.print(F(" "));
        };
    
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F(" change profile"));
        prt();
        status = 2;
    }
    
    goto_menu(&program::profile_menu, prev_sub);
    goto_menu(&program::rename_profile_menu, next_sub);
    
    if(ar_[incr_one] & (state::falling | state::auto_falling)) {
        if(active_profile_ + 1 < glob::n_profiles) {
            ++active_profile_;
            eeprom_ >> com::version(active_profile_) >> profile_;
        }
        prt();
    }
    if(ar_[decr_one] & (state::falling | state::auto_falling)) {
        if(active_profile_ > 0) {
            --active_profile_;
            eeprom_ >> com::version(active_profile_) >> profile_;
        }
        prt();
    }
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
    if(status <= 1) { //exit or menu change
        eeprom_ << active_profile_;
    }
}
void rename_profile_menu() {
    auto prt = [&](){
        lcd_.setCursor(4, 1);
        for(uint8_t i = 0; i < cursor_pos; ++i)
            lcd_.print(profile_.name[i]);
        lcd_.print(F("<"));
        lcd_.print(profile_.name[cursor_pos]);
        lcd_.print(F(">"));
        for(uint8_t i = cursor_pos + 1; i < glob::n_name - 1; ++i)
            lcd_.print(profile_.name[i]);
        lcd_.print(F(" "));
        
        };
    
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F(" rename profile"));
        cursor_pos = 0;
        prt();
        status = 2;
    }
    
    goto_menu(&program::change_profile_menu, prev_sub);
    goto_menu(&program::swap_profile_menu, next_sub);
    
    if(ar_[incr_one] & (state::falling | state::auto_falling)) {
        if(cursor_pos + 2 < glob::n_name)
            ++cursor_pos;
        prt();
    }
    if(ar_[decr_one] & (state::falling | state::auto_falling)) {
        if(cursor_pos > 0)
            --cursor_pos;
        prt();
    }
    if(ar_[incr_two] & (state::falling | state::auto_falling)) {
        char & c = profile_.name[cursor_pos];
        ++c;
        if(c == 0x21)
            c = 0x30;
        if(c == 0x3A)
            c = 0x41;
        if(c == 0x5B)
            c = 0x61;
        if(c == 0x7B)
            --c;
        prt();
    }
    if(ar_[decr_two] & (state::falling | state::auto_falling)) {
        char & c = profile_.name[cursor_pos];
        --c;
        if(c == 0x2F)
            c = 0x20;
        if(c == 0x40)
            c = 0x39;
        if(c == 0x60)
            c = 0x5A;
        if(c == 0x1F)
            ++c;
        
        prt();
    }
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
    if(status <= 1) { //exit or menu change
        eeprom_ << com::version(active_profile_) << profile_;
    }
}
void swap_profile_menu() {
    auto prt1 = [&](){
        eeprom_ >> com::version(cursor_pos) >> profile_;
        lcd_.setCursor(5, 0);
        lcd_.print(cursor_pos + 1);
        lcd_.print(F(" "));
        lcd_.setCursor(8, 0);
        lcd_.print(profile_.name.data());
        };
    auto prt2 = [&](){
        eeprom_ >> com::version(cursor_pos_2) >> profile_;
        lcd_.setCursor(5, 1);
        lcd_.print(cursor_pos_2 + 1);
        lcd_.print(F(" "));
        lcd_.setCursor(8, 1);
        lcd_.print(profile_.name.data());
        };
    
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("swap "));
        lcd_.setCursor(0, 1);
        
        lcd_.print(F("with "));
        cursor_pos = 0;
        cursor_pos_2 = 1;
        prt1();
        prt2();
        status = 2;
    }
    
    goto_menu(&program::rename_profile_menu, prev_sub);
    goto_menu(&program::copy_profile_menu, next_sub);
    
    if(ar_[incr_one] & (state::falling | state::auto_falling)) {
        if(cursor_pos + 1 < glob::n_profiles) {
            ++cursor_pos;
            if(cursor_pos == cursor_pos_2) {
                if(cursor_pos + 1 < glob::n_profiles)
                    ++cursor_pos;
                else
                    --cursor_pos;
            }
            prt1();
        }
    }
    if(ar_[decr_one] & (state::falling | state::auto_falling)) {
        if(cursor_pos > 0) {
            --cursor_pos;
            if(cursor_pos == cursor_pos_2) {
                if(cursor_pos > 0)
                    --cursor_pos;
                else
                    ++cursor_pos;
            }
            prt1();
        }
    }
    if(ar_[incr_two] & (state::falling | state::auto_falling)) {
        if(cursor_pos_2 + 1 < glob::n_profiles) {
            ++cursor_pos_2;
            if(cursor_pos == cursor_pos_2) {
                if(cursor_pos_2 + 1 < glob::n_profiles)
                    ++cursor_pos_2;
                else
                    --cursor_pos_2;
            }
            prt2();
        }
    }
    if(ar_[decr_two] & (state::falling | state::auto_falling)) {
        if(cursor_pos_2 > 0) {
            --cursor_pos_2;
            if(cursor_pos == cursor_pos_2) {
                if(cursor_pos_2 > 0)
                    --cursor_pos_2;
                else
                    ++cursor_pos_2;
            }
            prt2();
        }
    }
    if(ar_[ok] & state::falling) {
        eeprom_.swap_versions(profile_, cursor_pos, cursor_pos_2);
        if(cursor_pos == active_profile_)
            active_profile_ = cursor_pos_2;
        else if(cursor_pos_2 == active_profile_)
            active_profile_ = cursor_pos;
        eeprom_ << active_profile_;
        
        lcd_.clear();
        lcd_.print("   swap done!");
        usb_.delay_ms(500);
        status = 1;
    }
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
    if(status <= 1)
        eeprom_ >> com::version(active_profile_) >> profile_;
}
void copy_profile_menu() {
    auto prt1 = [&](){
        eeprom_ >> com::version(cursor_pos) >> profile_;
        lcd_.setCursor(5, 0);
        lcd_.print(cursor_pos + 1);
        lcd_.print(F(" "));
        lcd_.setCursor(8, 0);
        lcd_.print(profile_.name.data());
        };
    auto prt2 = [&](){
        eeprom_ >> com::version(cursor_pos_2) >> profile_;
        lcd_.setCursor(5, 1);
        lcd_.print(cursor_pos_2 + 1);
        lcd_.print(F(" "));
        lcd_.setCursor(8, 1);
        lcd_.print(profile_.name.data());
        };
    
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("copy "));
        lcd_.setCursor(0, 1);
        
        lcd_.print(F("  to "));
        cursor_pos = 0;
        cursor_pos_2 = 1;
        prt1();
        prt2();
        status = 2;
    }
    
    goto_menu(&program::swap_profile_menu, prev_sub);
    goto_menu(&program::profile_color_menu, next_sub);
    
    if(ar_[incr_one] & (state::falling | state::auto_falling)) {
        if(cursor_pos + 1 < glob::n_profiles) {
            ++cursor_pos;
            if(cursor_pos == cursor_pos_2) {
                if(cursor_pos + 1 < glob::n_profiles)
                    ++cursor_pos;
                else
                    --cursor_pos;
            }
            prt1();
        }
    }
    if(ar_[decr_one] & (state::falling | state::auto_falling)) {
        if(cursor_pos > 0) {
            --cursor_pos;
            if(cursor_pos == cursor_pos_2) {
                if(cursor_pos > 0)
                    --cursor_pos;
                else
                    ++cursor_pos;
            }
            prt1();
        }
    }
    if(ar_[incr_two] & (state::falling | state::auto_falling)) {
        if(cursor_pos_2 + 1 < glob::n_profiles) {
            ++cursor_pos_2;
            if(cursor_pos == cursor_pos_2) {
                if(cursor_pos_2 + 1 < glob::n_profiles)
                    ++cursor_pos_2;
                else
                    --cursor_pos_2;
            }
            prt2();
        }
    }
    if(ar_[decr_two] & (state::falling | state::auto_falling)) {
        if(cursor_pos_2 > 0) {
            --cursor_pos_2;
            if(cursor_pos == cursor_pos_2) {
                if(cursor_pos_2 > 0)
                    --cursor_pos_2;
                else
                    ++cursor_pos_2;
            }
            prt2();
        }
    }
    if(ar_[ok] & state::falling) {
        eeprom_ >> com::version(cursor_pos) >> profile_;
        eeprom_ << com::version(cursor_pos_2) << profile_;
        lcd_.clear();
        lcd_.print("   copy done!");
        usb_.delay_ms(500);
        status = 1;
    }
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
    if(status <= 1)
        eeprom_ >> com::version(active_profile_) >> profile_;
}
void profile_color_menu() {
    auto prt = [&](){
        lcd_.setCursor(4, 1);
        
        if(cursor_pos == 0)
            lcd_.print("<");
        else
            lcd_.print(" ");
        for(uint8_t i = 0; i < 3; ++i) {
            lcd_.print((int)profile_.color[i]);
            if(cursor_pos == i)
                lcd_.print(">");
            else if(cursor_pos == i + 1)
                lcd_.print("<");
            else
                lcd_.print(" ");
        }
        
        };
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("     R G B"));
        
        cursor_pos = 0;
        prt();
        status = 2;
    }
    
    goto_menu(&program::copy_profile_menu, prev_sub);
    goto_menu(&program::delete_profile_menu, next_sub);
    
    if(ar_[incr_one] & (state::falling | state::auto_falling)) {
        ++cursor_pos;
        cursor_pos %= 3;
        prt();
    }
    if(ar_[decr_one] & (state::falling | state::auto_falling)) {
        cursor_pos += 2;
        cursor_pos %= 3;
        prt();
    }
    if(ar_[incr_two] & (state::falling | state::auto_falling)) {
        if(profile_.color[cursor_pos] + 1 < glob::max_col) {
            ++profile_.color[cursor_pos];
            prt();
        }
    }
    if(ar_[decr_two] & (state::falling | state::auto_falling)) {
        if(profile_.color[cursor_pos] > 0) {
            --profile_.color[cursor_pos];
            prt();
        }
    }
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
    if(status <= 1) { //exit or menu change
        eeprom_ << com::version(active_profile_) << profile_;
    }
}
void delete_profile_menu() {
    auto prt = [&](){
        lcd_.setCursor(1, 1);
        lcd_.print(int(cursor_pos) + 1);
        lcd_.print(F(": "));
        lcd_.print(profile_.name.data());
        lcd_.print(F(" "));
        };
    
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F(" erase profile"));
        prt();
        status = 2;
        cursor_pos = 0;
        eeprom_ >> com::version(cursor_pos) >> profile_;
    }
    
    if(status == 2) {
        
        goto_menu(&program::profile_color_menu, prev_sub);
        
        if(ar_[incr_one] & (state::falling | state::auto_falling)) {
            if(active_profile_ + 1 < glob::n_profiles) {
                ++cursor_pos;
                eeprom_ >> com::version(cursor_pos) >> profile_;
            }
            prt();
        }
        if(ar_[decr_one] & (state::falling | state::auto_falling)) {
            if(cursor_pos > 0) {
                --cursor_pos;
                eeprom_ >> com::version(cursor_pos) >> profile_;
            }
            prt();
        }
        if(ar_[ok] & state::falling) {
            lcd_.clear();
            lcd_.print(F(" CONFIRME ERASE!"));
            status = 3;
        }
        if(ar_[menu_button_] & state::falling) {
            status = 0;
        }
        if(status <= 1) { //exit or menu change
            eeprom_ >> com::version(active_profile_) >> profile_;
        }
    } else {
        if(status == 3) {
            if(ar_[ok] & state::falling) {
                profile_ = profile_struct();
                eeprom_ << com::version(cursor_pos) << profile_;
                lcd_.print("profile erased!");
                usb_.delay_ms(500);
                status = 1;
            }
            if(ar_[abort] & state::falling)
                status = 1;
        }
    }
}
//  +---------------------------------------------------+
//  |                   display                         |
//  +---------------------------------------------------+
void display_menu() {
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("  display menu"));
        status = 2;
    }
    
    goto_menu(&program::light_menu, next_main);
    goto_menu(&program::profile_menu, prev_main);
    goto_menu(&program::time_menu, next_sub);
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
}
void time_menu() {
    auto prt = [&](){
        if(tool::clock.sec() > 3600) {
            lcd_.setCursor(4, 1);
            lcd_.print(int(tool::clock.sec()/3600));
            lcd_.print(":");
            if(int(tool::clock.sec()%3600)/60 < 10)
                lcd_.print("0");
        }
        else
            lcd_.setCursor(6, 1);
            
        if(int(tool::clock.sec()%3600)/60 > 0) {
            lcd_.print(int(tool::clock.sec()%3600)/60);
            lcd_.print(":");
            if(int(tool::clock.sec()%60) < 10)
                lcd_.print("0");
        }
        else
            lcd_.setCursor(7, 1);
            
        lcd_.print(int(tool::clock.sec()%60));
    };
    if(status == 0) {
        prt();
    } else {
        if(status == 1) {
            lcd_.clear();
            lcd_.print(F("  display time"));
            status = 2;
        }
        if(status == 2) {
            goto_menu(&program::display_menu, prev_sub);
            goto_menu(&program::disp_key_menu, next_sub);
        }
        if(ar_[menu_button_] & state::falling or status == 4) {
            lcd_.clear();
            lcd_.print(F("  time running"));
            disp_fct = &program::time_menu;
            disp_modus = 0;
            eeprom_ << disp_modus;
            status = 0;
        }
    }
}
//------------------- disp_key variables -------------------
void disp_key_menu() {
    auto prt = [&](){
            lcd_.setCursor(12, 0);
            lcd_.print(profile_.tier);
            lcd_.setCursor(2, 1);
            if(list.size() != 0) {
                uint8_t mod = 0;
                for(uint8_t i = 0; i < list.size(); ++i) {
                    mod |= profile_.mod(list[i]);
                }
                lcd_.print(mod_name(mod));
                lcd_.print(key_name(profile_.key(list.back())));
            }
            else {
                lcd_.print(mod_name(0));
                lcd_.print(key_name(1));
            }
        };
    
    auto action = [&](){
       for(uint8_t i = 0; i < glob::n_keys; ++i) {
            if(ar_[i] & (state::falling | state::raising)) {
                prt();
            }
        }
    };
    
    if(status == 0) {
        action();
    } else {
        if(status == 1) {
            lcd_.clear();
            lcd_.print(F("  display keys"));
            status = 2;
            list.clear();
        }
        if(status == 2) {
            goto_menu(&program::time_menu, prev_sub);
            goto_menu(&program::apm_menu, next_sub);
        }
        if(ar_[menu_button_] & state::falling or status == 4) {
            lcd_.clear();
            lcd_.setCursor(3, 0);
            lcd_.print(profile_.name.data());
            lcd_.setCursor(12, 0);
            lcd_.print(profile_.tier);
            list.clear();
            
            disp_fct = &program::disp_key_menu;
            disp_modus = 1;
            eeprom_ << disp_modus;
            status = 0;
        }
    }
}
//------------------- apm variables -------------------
ustd::array<uint8_t, glob::mean_1> apm_1;
ustd::array<uint8_t, glob::mean_2> apm_2;
uint8_t apm_pos_1;
uint8_t apm_pos_2;
uint16_t sum_1;
uint16_t sum_2;
void apm_menu() {
    //------------------- print -------------------
    auto prt = [&](){
        lcd_.setCursor(9, 1);
        lcd_.print(sum_1);
        lcd_.print(F("  "));
        lcd_.setCursor(13, 1);
        lcd_.print(sum_2);
        lcd_.print(F("  "));
    };
    auto clr = [&](){
        apm_pos_1 = tool::clock.sec() % glob::mean_1;
        apm_pos_2 = tool::clock.sec() % glob::mean_2;
        apm_1.clear();
        apm_2.clear();
        sum_1 = 0;
        sum_2 = 0;
        prt();
    };
    auto action = [&](){
        if(apm_pos_1 != (tool::clock.sec() % glob::mean_1)) {
            apm_pos_1 = tool::clock.sec() % glob::mean_1;
            apm_pos_2 = tool::clock.sec() % glob::mean_2;
            sum_1 -= apm_1[apm_pos_1];
            sum_2 -= apm_2[apm_pos_2];
            apm_1[apm_pos_1] = 0;
            apm_2[apm_pos_2] = 0;
            prt();
        }
        for(uint8_t i = 0; i < glob::n_keys; ++i) {
            if(ar_[i] & state::falling) {
                ++apm_1[apm_pos_1];
                ++sum_1;
                ++apm_2[apm_pos_2];
                ++sum_2;
                prt();
            }
        }
    };
    
    if(status == 0) {
        action();
    } else {
        if(status == 1) {
            lcd_.clear();
            lcd_.print(F("  display APM"));
            status = 2;
        }
        if(status == 2) {
            goto_menu(&program::disp_key_menu, prev_sub);
            goto_menu(&program::dark_menu, next_sub);
        }
        if(ar_[menu_button_] & state::falling or status == 4) {
            lcd_.clear();
            lcd_.print(F(" APM per 60s 5s"));
            clr();
            
            disp_fct = &program::apm_menu;
            disp_modus = 2;
            eeprom_ << disp_modus;
            status = 0;
        }
    }
}
void dark_menu() {
    if(status == 0) {
        if(lcd_led_.state() == state::pwm) {
            lcd_.clear();
            lcd_led_ = 255;
            lcd_led_ = state::off;
        }
    } else {
        if(status == 1) {
            lcd_.clear();
            lcd_.print(F("  display dark"));
            status = 2;
        }
        if(status == 2)
            goto_menu(&program::apm_menu, prev_sub);
        
        if(ar_[menu_button_] & state::falling or status == 4) {
            disp_fct = &program::dark_menu;
            disp_modus = 3;
            eeprom_ << disp_modus;
            status = 0;
        }
    }
}
//  +---------------------------------------------------+
//  |                   light                           |
//  +---------------------------------------------------+
void light_menu() {
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("   light menu"));
        status = 2;
    }
    
    goto_menu(&program::key_menu, next_main);
    goto_menu(&program::display_menu, prev_main);
    goto_menu(&program::shutter_menu, next_sub);
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
}
void shutter_menu() {
    auto prt = [&](){
        lcd_.setCursor(7, 1);
        lcd_.print(int(mcp_) - glob::mcp_low);
        lcd_.print("  ");
    };
    
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("    shutter"));
        prt();
        status = 2;
    }
    
    goto_menu(&program::light_menu, prev_sub);
    goto_menu(&program::lcd_led_menu, next_sub);
    
    if(ar_[incr_one] & (state::falling | state::auto_falling)) {
        if(mcp_ < glob::mcp_high)
            ++mcp_;
        prt();
    }
    if(ar_[decr_one] & (state::falling | state::auto_falling)) {
        if(mcp_ > glob::mcp_low)
            --mcp_;
        prt();
    }
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
    
    if(status <= 1) { //exit or menu change
        shutter_val_ = mcp_;
        eeprom_ << shutter_val_;
    }
}
void lcd_led_menu() {
    auto prt = [&](){
        lcd_.setCursor(7, 1);
        lcd_.print(int(lcd_led_val_));
        lcd_.print("  ");
    };
    
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("    lcd led"));
        prt();
        status = 2;
    }
    
    goto_menu(&program::shutter_menu, prev_sub);
    goto_menu(&program::led_high_menu, next_sub);
    
    if(ar_[incr_one] & (state::falling | state::auto_falling)) {
        if(lcd_led_val_ < 255)
            lcd_led_ = ++lcd_led_val_;
        prt();
    }
    if(ar_[decr_one] & (state::falling | state::auto_falling)) {
        if(lcd_led_val_ > 0)
            lcd_led_ = --lcd_led_val_;
        prt();
    }
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
    
    if(status <= 1) { //exit or menu change
        eeprom_ << lcd_led_val_;
    }
}
void led_high_menu() {
    auto prt = [&](){
        lcd_.setCursor(7, 1);
        lcd_.print(int(led_.high_power));
        lcd_.print("  ");
    };
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("    led high"));
        prt();
        status = 2;
    }
    
    goto_menu(&program::lcd_led_menu, prev_sub);
    goto_menu(&program::led_low_menu, next_sub);
    
    if(ar_[incr_one] & (state::falling | state::auto_falling)) {
        if(led_.high_power < glob::max_power)
            ++led_.high_power;
        prt();
    }
    if(ar_[decr_one] & (state::falling | state::auto_falling)) {
        if(led_.high_power > 0)
            --led_.high_power;
        prt();
    }
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
    
    if(status <= 1) { //exit or menu change
        eeprom_ << led_.high_power;
    }
}
void led_low_menu() {
    auto prt = [&](){
        lcd_.setCursor(7, 1);
        lcd_.print(int(led_.low_power));
        lcd_.print("  ");
    };
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("    led low"));
        prt();
        status = 2;
    }
    
    goto_menu(&program::led_high_menu, prev_sub);
    
    if(ar_[incr_one] & (state::falling | state::auto_falling)) {
        if(led_.low_power < glob::max_power)
            ++led_.low_power;
        prt();
    }
    if(ar_[decr_one] & (state::falling | state::auto_falling)) {
        if(led_.low_power > 0)
            --led_.low_power;
        prt();
    }
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
    
    if(status <= 1) { //exit or menu change
        eeprom_ << led_.low_power;
    }
}
//  +---------------------------------------------------+
//  |                   key                             |
//  +---------------------------------------------------+
void key_menu() {
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("    key menu"));
        status = 2;
    }
    
    goto_menu(&program::main_menu, next_main);
    goto_menu(&program::light_menu, prev_main);
    
    goto_menu(&program::change_key_menu, next_sub);
    if(ar_[menu_button_] & state::falling) {
        status = 0;
    }
}
//------------------- change key variables -------------------
uint8_t select_key;
void change_key_menu() {
    auto prt = [&]() {
        lcd_.setCursor(15, 0);
        lcd_.print(profile_.tier);
        lcd_.setCursor(1, 1);
        lcd_.print(mod_name(cursor_pos));
        lcd_.setCursor(9, 1);
        lcd_.print(key_name(cursor_pos_2));
    };
    
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("   change key"));
        status = 2;
    }
    if(status == 2) {
        if(ar_[ok] & state::falling) {
            lcd_.clear();
            lcd_.print(F("   target key"));
            status = 3;
        }
        goto_menu(&program::key_menu, prev_sub);
        goto_menu(&program::change_menu_btn_menu, next_sub);
        if(ar_[menu_button_] & state::falling) {
            status = 0;
        }
    } else
    if(status == 3) {
        for(uint8_t i = 0; i < glob::n_keys; ++i) {
            if(ar_[i] & state::falling) {
                select_key = i;
                status = 5;
                break;
            }
        }
    } else
    if(status == 6 or status == 5) {
        if(status == 5) {
            lcd_.clear();
            lcd_.print(F("new key / tier "));
            profile_.tier = 0;
            lcd_.print(profile_.tier);
            cursor_pos = profile_.mod(select_key);
            cursor_pos_2 = profile_.key(select_key);
            prt();
            status = 6;
        }
        if(status == 6) {
            if(ar_[next_sub] & (state::falling | state::auto_falling)) {
                if(profile_.tier + 1 < glob::n_tiers) {
                    profile_.mod(select_key) = cursor_pos;
                    profile_.key(select_key) = cursor_pos_2;
                    ++profile_.tier;
                    cursor_pos = profile_.mod(select_key);
                    cursor_pos_2 = profile_.key(select_key);
                    prt();
                }
            }
            if(ar_[prev_sub] & (state::falling | state::auto_falling)) {
                if(profile_.tier > 0) {
                    profile_.mod(select_key) = cursor_pos;
                    profile_.key(select_key) = cursor_pos_2;
                    --profile_.tier;
                    cursor_pos = profile_.mod(select_key);
                    cursor_pos_2 = profile_.key(select_key);
                    prt();
                }
            }
            if(ar_[incr_one] & (state::falling | state::auto_falling)) {
                if(cursor_pos + 1 < 16) {
                    ++cursor_pos;
                    prt();
                }
            }
            if(ar_[decr_one] & (state::falling | state::auto_falling)) {
                if(cursor_pos > 0) {
                    --cursor_pos;
                    prt();
                }
            }
            if(ar_[incr_two] & (state::falling | state::auto_falling)) {
                if(cursor_pos_2 + 1 < 133) {
                    if(cursor_pos_2 == 0)
                        cursor_pos_2 = 4;
                    else
                        ++cursor_pos_2;
                    if(cursor_pos_2 == 116)
                        cursor_pos_2 = 127;
                    prt();
                }
            }
            if(ar_[decr_two] & (state::falling | state::auto_falling)) {
                if(cursor_pos_2 > 3) {
                    --cursor_pos_2;
                    if(cursor_pos_2 == 3)
                        cursor_pos_2 = 0;
                    if(cursor_pos_2 == 126)
                        cursor_pos_2 = 115;
                    prt();
                }
            }
            if(ar_[ok] & state::falling) {
                if(cursor_pos_2 >= glob::tier[0]) {
                    profile_.mod(select_key) = (uint8_t)key::none;
                    profile_.key(select_key) = cursor_pos_2;
                    cursor_pos = profile_.tier;
                    profile_.tier = cursor_pos_2 - glob::tier[0];
                    profile_.mod(select_key) = (uint8_t)key::none;
                    profile_.key(select_key) = glob::tier[0] + cursor_pos;
                } else {
                    profile_.mod(select_key) = cursor_pos;
                    profile_.key(select_key) = cursor_pos_2;
                }
                profile_.tier = 0;
                
                eeprom_ << com::version(active_profile_) << profile_;
                lcd_.clear();
                lcd_.print("  change done!");
                usb_.delay_ms(500);
                status = 1;
            }
            if(ar_[abort] & state::falling)
                status = 1;
        }
    }
}
void change_menu_btn_menu() {
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("change menu key"));
        status = 2;
    }
    if(status == 2) {
        if(ar_[ok] & state::falling) {
            lcd_.clear();
            lcd_.print(F("   target key"));
            status = 3;
        }
        goto_menu(&program::change_key_menu, prev_sub);
        goto_menu(&program::copy_key_menu, next_sub);
        if(ar_[menu_button_] & state::falling) {
            status = 0;
        }
    } else
    if(status == 3) {
        for(uint8_t i = 0; i < glob::n_keys; ++i) {
            if(ar_[i] & state::falling) {
                menu_button_ = i;
                for(uint8_t k = 0; k < glob::n_tiers; ++k) {
                    profile_.tier = k;
                    profile_.key(menu_button_) = (uint8_t)key::none;
                    profile_.mod(menu_button_) = (uint8_t)key::none;
                }
                profile_.tier = 0;
                
                eeprom_ << menu_button_;
                lcd_.clear();
                lcd_.print("  change done!");
                usb_.delay_ms(500);
                status = 1;
            }
        }
    }
}
void copy_key_menu() {
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F("   copy key"));
        status = 2;
    }
    if(status == 2) {
        goto_menu(&program::change_menu_btn_menu, prev_sub);
        goto_menu(&program::reset_keys_menu, next_sub);
        
        if(ar_[ok] & state::falling) {
            lcd_.clear();
            lcd_.print(F("   source key"));
            status = 3;
        }
        if(ar_[menu_button_] & state::falling) {
            status = 0;
        }
    } else
    if(status == 3) {
        for(uint8_t i = 0; i < glob::n_keys; ++i) {
            if(ar_[i] & state::falling) {
                select_key = i;
                status = 5;
            }
        }
    } else if(status == 6 or status == 5) {
        if(status == 5) {
            lcd_.clear();
            lcd_.print(F("   target key"));
            status = 6;
        }
        if(status == 6) {
            for(uint8_t i = 0; i < glob::n_keys; ++i) {
                if(ar_[i] & state::falling) {
                    for(uint8_t k = 0; k < glob::n_tiers; ++k) {
                        profile_.tier = k;
                        profile_.mod(i) = profile_.mod(select_key);
                        profile_.key(i) = profile_.key(select_key);
                    }
                    profile_.tier = 0;
                    eeprom_ << com::version(active_profile_) << profile_;
                    
                    lcd_.clear();
                    lcd_.print("   copy done!");
                    usb_.delay_ms(500);
                    status = 1;
                }
            }
        }
    }
}
void reset_keys_menu() {
    if(status == 1) {
        lcd_.clear();
        lcd_.print(F(" erase all keys"));
        status = 2;
    }
    if(status == 2) {
        goto_menu(&program::change_menu_btn_menu, prev_sub);
        goto_menu(&program::reset_keys_menu, next_sub);
        if(ar_[ok] & state::falling) {
            lcd_.clear();
            lcd_.print(F(" CONFIRME ERASE!"));
            status = 3;
        }
        if(ar_[menu_button_] & state::falling) {
            status = 0;
        }
    } else if(status == 3) {
        for(uint8_t i = 0; i < glob::n_keys; ++i) {
            if(ar_[ok] & state::falling) {
                for(uint8_t k = 0; k < glob::n_tiers; ++k) {
                    for(uint8_t i = 0; i < glob::n_keys; ++i) {
                        profile_.tier = k;
                        profile_.mod(i) = (uint8_t)key::none;
                        profile_.key(i) = (uint8_t)key::none;
                    }
                }
                profile_.tier = 0;
                lcd_.clear();
                eeprom_ << com::version(active_profile_) << profile_;
                lcd_.print("  keys erased!");
                usb_.delay_ms(500);
                status = 1;
            }
            if(ar_[abort] & state::falling)
                status = 1;
        }
    }
}
#endif //__MENU_METHODS_HEADER
