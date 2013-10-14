// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    23.05.2013 23:36:55 EDT
// File:    serial_menu.hpp

#ifndef __SERIAL_MENU_HEADER
#define __SERIAL_MENU_HEADER

#include "ustd/iostream.hpp"

namespace detail {
    template<typename fct_ptr>
    struct fake_map {
        void add(ustd::string const n, fct_ptr f, fct_ptr h) {
            ASSERT(name.find(n) == name.end())
            name.push_back(n);
            fct.push_back(f);
            help.push_back(h);
        }
        fct_ptr operator[](ustd::string const n) {
            ASSERT((name.find(n) != name.end()))
            auto pos = name.find(n);
            return fct[pos];
        }
        fct_ptr operator()(ustd::string const n, uint8_t const choice) {
            ASSERT((name.find(n) != name.end()))
            auto pos = name.find(n);
            if(choice == 0)
                return fct[pos];
            return help[pos];
        }
        ustd::vector<ustd::string> name;
        ustd::vector<fct_ptr> fct;
        ustd::vector<fct_ptr> help;
    };
}//end namespace detail

enum class format {
      chr
    , dec
    , num
    , bin
    , hex
};
enum class read_enum : uint8_t {
      space_out
    , enter_out
    , limit_out
    , normal
    , silent
};

template<uint8_t max_cmd = 10, uint8_t max_arg = 5>
class serial_menu_class {
    
    using fct_ptr = void (*)(uint8_t *);
    
    template<typename T>
    read_enum read_part(T * buf, uint8_t const max_size, format const & f, read_enum const & silent) {
        const uint8_t key_enter = 13;
        const uint8_t key_escape = 27;
        const uint8_t key_space = 32;
        const uint8_t key_comma = 44;
        
        
        T temp = 0;
        format loc_f = f;
        for(uint8_t i = 0; i < max_size; ++i) {
            ustd::cin >> temp;
            switch(temp) {
                case(key_escape):
                    delayMicroseconds(350);
                    if(ustd::cin) {
                        while(Serial.available())
                            Serial.read();
                        --i;
                    }
                    else
                        ustd::cout << buf[i];
                    break;
                case(key_enter):
                    if(loc_f != format::chr) {
                        ustd::cout << F("(") << buf[i] << F(")");
                    }
                    else
                        buf[i] = 0;
                    return read_enum::enter_out;
                    break;
                case(key_space):
                    temp = 0;
                    if(loc_f != format::chr) {
                        ustd::cout << F("(") << buf[i] << F(")");
                    }
                    else {
                        if(silent == read_enum::silent)
                            ustd::cout << F(" ");
                        buf[i] = 0;
                    }
                    return read_enum::space_out;
                    break;
                case(key_comma):
                    if(loc_f != format::chr) {
                        ustd::cout << F("(") << buf[i] << F("), ");
                        loc_f = f;
                        break;
                    }
                default:
                    if(loc_f == format::chr) {
                        if(silent == read_enum::silent)
                            ustd::cout << temp;
                        buf[i] = temp;
                    }
                    else if(loc_f == format::bin) {
                        if(temp == '0' or temp == '1') {
                            ustd::cout << char(temp);
                            buf[i] <<= 1;
                            buf[i] += temp - '0';
                        }
                        --i;
                    }
                    else if(loc_f == format::num and (temp == 'x' or temp == 'b')) {
                        if(temp == 'x') {
                            ustd::cout << char(temp);
                            loc_f = format::hex;
                        }
                        else if(temp == 'b') {
                            ustd::cout << char(temp);
                            loc_f = format::bin;
                        }
                        --i;
                    }
                    else if(loc_f == format::dec or loc_f == format::num) {
                        if(temp >= '0' and temp <= '9') {
                            loc_f = format::dec;
                            ustd::cout << char(temp);
                            buf[i] *= 10;
                            buf[i] += temp - '0';
                        }
                        --i;
                    }
                    else if(loc_f == format::hex) {
                        if((temp >= '0' and temp <= '9') or (temp >= 'A' and temp <= 'F')) {
                            ustd::cout << char(temp);
                            buf[i] *= 16;
                            buf[i] += temp - (temp > '9' ? ('A' - 10) : '0');
                        }
                        --i;
                    }
                    break;
            }
        }
        return read_enum::limit_out;
    }
public:
    serial_menu_class() {
    }
    ustd::string const get_line(format const & f = format::chr, read_enum const & silent = read_enum::normal){
        if(read_part(cmd_, max_cmd, format::chr, silent) == read_enum::space_out) {
            for(uint8_t i = 0; i < max_arg; ++i) {
                cmd_arg_[i] = 0;
            }
            read_part(cmd_arg_, max_arg, f, silent);
        }
        //~ DEBUG_VAR(cmd_)
        //~ for(uint8_t i = 0; i < max_arg; ++i) {
            //~ DEBUG_VAR(cmd_arg_[i])
        //~ }
        return cmd_;
    }
    void add(ustd::string const n, fct_ptr const & f, fct_ptr const & h) {
        fmap.add(n, f, h);
    }
    void use_fct() {
        if(fmap.name.find(cmd_) != fmap.name.end()) {
            fmap[cmd_](cmd_arg_);
            return;
        }
        if(strncmp(cmd_, "help", 4) == 0) {
            char * cmd = (cmd_ + 5);
            if(fmap.name.find(cmd) != fmap.name.end()) {
                ustd::cout << F("help for ") << cmd << F(": ");
                fmap(cmd, 1)(cmd_arg_);
                return;
            }
        }
        possibilities();
    }
    void possibilities() {
        ustd::cout << F("no match, try: [");
        for(uint8_t j = 0; j < fmap.name.size(); ++j) {
            ustd::cout << F("\"") << fmap.name[j];
            if(j != fmap.name.size() - 1)
                ustd::cout << F("\", ");
        }
        ustd::cout << F("\"]") << ustd::endl;
    }
private:
    char cmd_[max_cmd];
    uint8_t cmd_arg_[max_arg];
    detail::fake_map<fct_ptr> fmap;
};
#endif //__SERIAL_MENU_HEADER
