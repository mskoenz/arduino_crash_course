// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    21.06.2013 18:02:19 EDT
// File:    my_lib.cpp

#include <assert.h>

#include <logic.hpp>

//~ #include <chrono>
//~ #include <thread>
    //~ std::this_thread::sleep_for(std::chrono::microseconds(200));

serial_class Serial;

//------------------- support for std::map -------------------
template<typename K, typename V>
K const & find_key(std::map<K, V> const & m, V const & val) {
    for(auto it = m.cbegin(); it != m.cend(); ++it) {
        if(it->second == val)
            return it->first;
    }
}


logic_struct::logic_struct(): 
      uart(Serial)
    , sen()
    , n_gest(0)
{
    con = Serial.init("/dev/ttyUSB0", keyop::speed);

//------------------- init key_map -------------------
    key_map["no key"] = (uint8_t)key::none;
    key_map["a"] = (uint8_t)key::a;
    key_map["b"] = (uint8_t)key::b;
    key_map["c"] = (uint8_t)key::c;
    key_map["d"] = (uint8_t)key::d;
    key_map["e"] = (uint8_t)key::e;
    key_map["f"] = (uint8_t)key::f;
    key_map["g"] = (uint8_t)key::g;
    key_map["h"] = (uint8_t)key::h;
    key_map["i"] = (uint8_t)key::i;
    key_map["j"] = (uint8_t)key::j;
    key_map["k"] = (uint8_t)key::k;
    key_map["l"] = (uint8_t)key::l;
    key_map["m"] = (uint8_t)key::m;
    key_map["n"] = (uint8_t)key::n;
    key_map["o"] = (uint8_t)key::o;
    key_map["p"] = (uint8_t)key::p;
    key_map["q"] = (uint8_t)key::q;
    key_map["r"] = (uint8_t)key::r;
    key_map["s"] = (uint8_t)key::s;
    key_map["t"] = (uint8_t)key::t;
    key_map["u"] = (uint8_t)key::u;
    key_map["v"] = (uint8_t)key::w;
    key_map["w"] = (uint8_t)key::w;
    key_map["x"] = (uint8_t)key::x;
    key_map["y"] = (uint8_t)key::y;
    key_map["z"] = (uint8_t)key::z;
    
    key_map["k1"] = (uint8_t)key::k1;
    key_map["k2"] = (uint8_t)key::k2;
    key_map["k3"] = (uint8_t)key::k3;
    key_map["k4"] = (uint8_t)key::k4;
    key_map["k5"] = (uint8_t)key::k5;
    key_map["k6"] = (uint8_t)key::k6;
    key_map["k7"] = (uint8_t)key::k7;
    key_map["k8"] = (uint8_t)key::k8;
    key_map["k9"] = (uint8_t)key::k9;
    key_map["k0"] = (uint8_t)key::k0;
    
    key_map["enter"] = (uint8_t)key::enter;
    key_map["escape"] = (uint8_t)key::escape;
    key_map["backspace"] = (uint8_t)key::backspace;
    key_map["tab"] = (uint8_t)key::tab;
    key_map["space"] = (uint8_t)key::space;
    key_map["minus"] = (uint8_t)key::minus;
    key_map["circumflex"] = (uint8_t)key::circumflex;
    key_map["ue"] = (uint8_t)key::ue;
    key_map["diaresis"] = (uint8_t)key::diaresis;
    key_map["dollar"] = (uint8_t)key::dollar;
    
    key_map["oe"] = (uint8_t)key::oe;
    key_map["ae"] = (uint8_t)key::ae;
    key_map["section"] = (uint8_t)key::section;
    key_map["comma"] = (uint8_t)key::comma;
    key_map["dot"] = (uint8_t)key::dot;
    
    key_map["caps_lock"] = (uint8_t)key::caps_lock;
    key_map["F1"] = (uint8_t)key::F1;
    key_map["F2"] = (uint8_t)key::F2;
    key_map["F3"] = (uint8_t)key::F3;
    key_map["F4"] = (uint8_t)key::F4;
    key_map["F5"] = (uint8_t)key::F5;
    key_map["F6"] = (uint8_t)key::F6;
    key_map["F7"] = (uint8_t)key::F7;
    key_map["F8"] = (uint8_t)key::F8;
    key_map["F9"] = (uint8_t)key::F9;
    key_map["F10"] = (uint8_t)key::F10;
    key_map["F11"] = (uint8_t)key::F11;
    key_map["F12"] = (uint8_t)key::F12;
    key_map["prt_scr"] = (uint8_t)key::prt_scr;
    key_map["scr_lock"] = (uint8_t)key::scr_lock;
    key_map["pause"] = (uint8_t)key::pause;
    key_map["insert"] = (uint8_t)key::insert;
    key_map["home"] = (uint8_t)key::home;
    key_map["page_up"] = (uint8_t)key::page_up;
    key_map["del"] = (uint8_t)key::del;
    key_map["end"] = (uint8_t)key::end;
    key_map["page_down"] = (uint8_t)key::page_down;
    key_map["right"] = (uint8_t)key::right;
    key_map["left"] = (uint8_t)key::left;
    key_map["down"] = (uint8_t)key::down;
    key_map["up"] = (uint8_t)key::up;
    key_map["num_lock"] = (uint8_t)key::num_lock;
    
    key_map["pad_div"] = (uint8_t)key::pad_div;
    key_map["pad_mult"] = (uint8_t)key::pad_mult;
    key_map["pad_minus"] = (uint8_t)key::pad_minus;
    key_map["pad_plus"] = (uint8_t)key::pad_plus;
    key_map["pad_enter"] = (uint8_t)key::pad_enter;
    key_map["pad_1"] = (uint8_t)key::pad_1;
    key_map["pad_2"] = (uint8_t)key::pad_2;
    key_map["pad_3"] = (uint8_t)key::pad_3;
    key_map["pad_4"] = (uint8_t)key::pad_4;
    key_map["pad_5"] = (uint8_t)key::pad_5;
    key_map["pad_6"] = (uint8_t)key::pad_6;
    key_map["pad_7"] = (uint8_t)key::pad_7;
    key_map["pad_8"] = (uint8_t)key::pad_8;
    key_map["pad_9"] = (uint8_t)key::pad_9;
    key_map["pad_0"] = (uint8_t)key::pad_0;
    key_map["pad_dot"] = (uint8_t)key::pad_dot;
    key_map["angle"] = (uint8_t)key::angle;
    
    key_map["power"] = (uint8_t)key::power;
    key_map["pad_equal"] = (uint8_t)key::pad_equal;
    
    key_map["F13"] = (uint8_t)key::F13;
    key_map["F14"] = (uint8_t)key::F14;
    key_map["F15"] = (uint8_t)key::F15;
    key_map["F16"] = (uint8_t)key::F16;
    key_map["F17"] = (uint8_t)key::F17;
    key_map["F18"] = (uint8_t)key::F18;
    key_map["F19"] = (uint8_t)key::F19;
    key_map["F20"] = (uint8_t)key::F20;
    key_map["F21"] = (uint8_t)key::F21;
    key_map["F22"] = (uint8_t)key::F22;
    key_map["F23"] = (uint8_t)key::F23;
    key_map["F24"] = (uint8_t)key::F24;
    
    key_map["mute"] = (uint8_t)key::mute;
    key_map["volume_up"] = (uint8_t)key::volume_up;
    key_map["volume_down"] = (uint8_t)key::volume_down;

//------------------- init mod_map -------------------
    mod_map["no mod"] = (uint8_t)key::none;
    mod_map["ctrl"] = (uint8_t)key::ctrl;
    mod_map["shift"] = (uint8_t)key::shift;
    mod_map["ctrl + shift"] = (uint8_t)key::ctrl + (uint8_t)key::shift;
    mod_map["alt"] = (uint8_t)key::alt;
    mod_map["alt + ctrl"] = (uint8_t)key::alt + (uint8_t)key::ctrl;
    mod_map["alt + shift"] = (uint8_t)key::alt + (uint8_t)key::shift;
    mod_map["alt + ctrl + shift"] = (uint8_t)key::alt + (uint8_t)key::shift + (uint8_t)key::ctrl;
    mod_map["gui"] = (uint8_t)key::gui;
    mod_map["gui + ctrl"] = (uint8_t)key::gui + (uint8_t)key::ctrl;
    mod_map["gui + shift"] = (uint8_t)key::gui + (uint8_t)key::shift;
    mod_map["gui + ctrl + shift"] = (uint8_t)key::gui + (uint8_t)key::ctrl + (uint8_t)key::shift;
    mod_map["gui + alt"] = (uint8_t)key::gui + (uint8_t)key::alt;
    mod_map["gui + alt + ctrl"] = (uint8_t)key::gui + (uint8_t)key::alt + (uint8_t)key::ctrl;
    mod_map["gui + alt + shift"] = (uint8_t)key::gui + (uint8_t)key::alt + (uint8_t)key::shift;
    mod_map["gui + alt + ctrl + shift"] = (uint8_t)key::gui + (uint8_t)key::alt + (uint8_t)key::shift + (uint8_t)key::ctrl;

    
//------------------- init acc_map -------------------
    acc_map["all"] = 0;
    acc_map["+x"] = 1;
    acc_map["-x"] = 2;
    acc_map["+y"] = 3;
    acc_map["-y"] = 4;
    acc_map["+z"] = 5;
    acc_map["-z"] = 6;
}

bool logic_struct::connected() const {
    return con;
}

void logic_struct::raw_value() {
    uart << core::raw_value;
    uart >> sen;
}
void logic_struct::write_gest(id_type const & id) {
    uart << core::write_gesture << id;
    uart << gest[id];
}
void logic_struct::write_all_gest() {
    write_n_gest();
    for(uint i = 0; i < n_gest; ++i) {
        write_gest(i);
    }
}
void logic_struct::read_gest(id_type const & id) {
    uart << core::read_gesture << id;
    uart >> gest[id];
}
void logic_struct::read_all_gest() {
    read_n_gest();
    for(uint i = 0; i < n_gest; ++i) {
        read_gest(i);
    }
}
void logic_struct::read_n_gest() {
    uart << core::read_n_gestures;
    uart >> n_gest;
}
void logic_struct::write_n_gest() {
    uart << core::write_n_gestures;
    uart << n_gest;
}
void logic_struct::send_cmd(uint8_t const & cmd) {
    uart << cmd;
}
void logic_struct::write_key(id_type const & id) {
    uart << keyop::write_key << id;
    
    //------------------- main key -------------------
    uint8_t key = key_map.at(key_meta[id].key);
    uint8_t mod = mod_map.at(key_meta[id].mod);
    uint8_t trigger = (acc_map.at(key_meta[id].acc) << 5) + (key_meta[id].id & 31);
    uart << key << mod << trigger;
    //------------------- pre key -------------------
    key = key_map.at(key_meta[id].pre_key);
    mod = mod_map.at(key_meta[id].pre_mod);
    trigger = (acc_map.at(key_meta[id].pre_acc) << 5) + (key_meta[id].pre_id & 31);
    uart << key << mod << trigger;
}
void logic_struct::write_all_keys() {
    write_n_keys();
    for(uint i = 0; i < logic.n_keys; ++i) {
        write_key(i);
    }
}
void logic_struct::read_key(id_type const & id) {
    uart << keyop::read_key << id;
    uint8_t key;
    uint8_t mod;
    uint8_t trigger;
    //------------------- main key -------------------
    uart >> key >> mod >> trigger;
    
    uint8_t acc = (trigger >> 5);
    uint8_t _id = (trigger & 31);
    
    key_meta[id].id = _id;
    key_meta[id].key = find_key(key_map, key);
    key_meta[id].mod = find_key(mod_map, mod);
    key_meta[id].acc = find_key(acc_map, acc);
    
    //------------------- pre key -------------------
    uart >> key >> mod >> trigger;
    
    acc = (trigger >> 5);
    _id = (trigger & 31);
    
    key_meta[id].pre_id = _id;
    key_meta[id].pre_key = find_key(key_map, key);
    key_meta[id].pre_mod = find_key(mod_map, mod);
    key_meta[id].pre_acc = find_key(acc_map, acc);
}
void logic_struct::read_all_keys() {
    read_n_keys();
    for(uint i = 0; i < logic.n_keys; ++i) {
        read_key(i);
    }
}

void logic_struct::read_n_keys() {
    uart << keyop::read_n_keys;
    uart >> n_keys;
}
void logic_struct::write_n_keys() {
    uart << keyop::write_n_keys;
    uart << n_keys;
}

logic_struct logic;
