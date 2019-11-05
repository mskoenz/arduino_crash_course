// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    21.06.2013 18:00:12 EDT
// File:    my_header.hpp

#ifndef __MY_HEADER_HEADER
#define __MY_HEADER_HEADER

#include <iostream>
#include <array>
#include <map>

#include <std_support.hpp>
#include <com/fio.hpp>
#include <device/hid_keys.hpp>
#include "../../atmega_src/bridge.hpp"
#include "../../atmega_src/keyop_protocol.hpp"

typedef uint8_t id_type;
typedef uint8_t val_type;

struct key_meta_struct {
    key_meta_struct(): name("no name"), id(0), key("no key"), mod("no mod"), acc("all")
    , pre_id(0), pre_key("no key"), pre_mod("no mod"), pre_acc("all") 
    {
    }
    
    std::string name;
    
    uint8_t id;
    std::string key;
    std::string mod;
    std::string acc;
    
    uint8_t pre_id;
    std::string pre_key;
    std::string pre_mod;
    std::string pre_acc;
    
    template<typename Archive>
    void serialize(Archive & ar) {
        ar & name;
        ar & key;
        ar & mod;
        ar & id;
        ar & acc;
        
        ar & pre_key;
        ar & pre_mod;
        ar & pre_id;
        ar & pre_acc;
    }
};
struct gest_meta_struct {
    gest_meta_struct(): name("no name") {
    }
    
    std::string name;
    
    template<typename Archive>
    void serialize(Archive & ar) {
        ar & name;
    }
};

struct logic_struct {
    logic_struct();
    //------------------- uart -------------------
    bool connected() const;
    com::uart_class_template<serial_class> uart;
    bool con;
    
    //------------------- data glove i2c -------------------
    void raw_value();
    void write_gest(id_type const & id);
    void write_all_gest();
    void read_gest(id_type const & id);
    void read_all_gest();
    void read_n_gest();
    void write_n_gest();
    void send_cmd(uint8_t const & cmd);
    
    void write_key(id_type const & id);
    void write_all_keys();
    void read_key(id_type const & id);
    void read_all_keys();
    void read_n_keys();
    void write_n_keys();
    
    std::array<val_type, 9> sen;
    uint8_t n_gest;
    gesture_class gest[core::max_gest];
    gest_meta_struct gest_meta[core::max_gest];
    
    uint8_t n_keys;
    key_meta_struct key_meta[keyop::max_keys];
    std::map<std::string, uint8_t> key_map;
    std::map<std::string, uint8_t> mod_map;
    std::map<std::string, uint8_t> acc_map;
    
    
    //------------------- archive -------------------
    com::fio_class fio_;
    
    void read_archive(std::string const & path_name) {
        fio_.open_read(path_name);
        
        fio_ >> n_gest;
        fio_ >> n_keys;
        fio_ >> gest;
        fio_ >> gest_meta;
        fio_ >> key_meta;
        
        fio_.close();
    }
    void write_archive(std::string const & path_name) {
        fio_.open_write(path_name);
        
        fio_ << n_gest;
        fio_ << n_keys;
        fio_ << gest;
        fio_ << gest_meta;
        fio_ << key_meta;
        
        fio_.close();
    }
    
};
extern logic_struct logic;

#endif //__MY_HEADER_HEADER
