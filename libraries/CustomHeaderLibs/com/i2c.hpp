// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    09.06.2013 19:43:04 EDT
// File:    i2c_io.hpp

#ifndef __I2C_IO_HEADER
#define __I2C_IO_HEADER

#include "serializer.hpp"
#include "../ustd/static_vector.hpp"

#include <Wire.h>

void requestEvent();
void receiveEvent(int);

namespace com {
    class i2cout_class {
    public:
        static archive_enum const type = archive_enum::output;
        
        i2cout_class(): target_(255) {
        }
        template<typename T>
        i2cout_class & operator<<(T && t) {
            return (*this) & t;
        }
        /* old ugly version / T && t (see above) fixed the problem
        * template<typename T>
        * i2cout_class & operator<<(T const & t) {
        *     T t2(t); //TODO: super ugly, remove asap
        *     return (*this) & t2;
        * } 
        * */
        template<typename T>
        i2cout_class & operator&(T & t) {
            serialize(*this, t);
            return (*this);
        }
        i2cout_class & operator<<(ustd::endl_class & endl_) {
            if(target_ != 255)
                Wire.beginTransmission(target_);
            
            Wire.write(data_.data(), data_.size());
            data_.clear();
            
            if(target_ != 255) {
                Wire.endTransmission(endl_.end);
                endl_(true);
            }
            
            return (*this);
        }
        void write(byte const & in) {
            data_.push_back(in);
        }
        i2cout_class & operator()(uint8_t const & adr_) {
            target_ = adr_;
            return (*this);
        }
        
        
    private:
        uint8_t target_;
        ustd::static_vector<byte, 32> data_;
    } i2cout;

    class i2cin_class {
    public:
        static archive_enum const type = archive_enum::input;
        
        i2cin_class(): target_(255) {
        }
        
        template<typename T>
        i2cin_class & operator>>(T & t) {
            if(target_ != 255) {
                #ifdef __TYPE_SIZE_CHECK
                    Wire.requestFrom(target_, sizeof(T) + 1);
                    while(Wire.available() != (sizeof(T)+1)) DEBUG_MSG("FAIL: To earley");
                #else //__TYPE_SIZE_CHECK
                    Wire.requestFrom(target_, sizeof(T));
                    while(Wire.available() != sizeof(T)) DEBUG_MSG("FAIL: To earley");
                #endif //__TYPE_SIZE_CHECK
            }
            return ((*this) & t);
        }
        template<typename T>
        i2cin_class & operator&(T & t) {
            serialize(*this, t);
            return (*this);
        }
        
        byte read() {
            return Wire.read();
        }
        
        uint8_t available() {
            return Wire.available();
        }
        i2cin_class & operator()(uint8_t const & adr_) {
            target_ = adr_;
            return (*this);
        }
    private:
        uint8_t target_;
    } i2cin;

    void i2c_begin() {
        Wire.begin();
        delay(5);
    }
    void i2c_begin(int const & adr, void (*rec)(int) = receiveEvent, void (*req)(void) = requestEvent) {
        Wire.begin(adr);
        Wire.onRequest(req); // register event
        Wire.onReceive(rec);
    }
}//end namespace com
#endif //__I2C_IO_HEADER
