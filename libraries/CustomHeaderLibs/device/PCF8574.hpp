// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    19.08.2013 22:29:52 CEST
// File:    PCF8574.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __PCF8574_HEADER
#define __PCF8574_HEADER

#include "../com/i2c.hpp"
#include "../util/byte_operation.hpp"

namespace device {
    class PCF8574_class {
    public:
        PCF8574_class(uint8_t const & add): dev_ard_(0x20 + add), input_mask_(0) { //the addres is 0x20 + (A2 << 2 | A1 << 1 | A0)
        }
        void write(uint8_t const & data) { //if a write happens put input bits high
            com::i2cout(dev_ard_) << uint8_t(data | input_mask_) << ustd::endl;
        }
        //use low to drive high (25mA per port) currents. Continuouse high works with 300uA per port...
        uint8_t read() const {
            uint8_t res;
            com::i2cin(dev_ard_) >> res;
            return res;
        }
        uint8_t & mask() {
            return input_mask_;
        }
    private:
        uint8_t dev_ard_;
        uint8_t input_mask_; //the imputs should always be written HIGH
    };
}//end namespace device

namespace tool {
    template<uint8_t pin>
    class PCF8574 {
    public:
        PCF8574(device::PCF8574_class & ioexp): ioexp_(&ioexp), pm_set_(false) {
        }
        void mode(uint8_t const & pm) {
            pm_set_ = false; //since i2c isn't online yet...
            if(pm == INPUT_PULLUP or pm == INPUT) {
                util::set_bit(ioexp_->mask(), pin);
            }
            else
                util::clear_bit(ioexp_->mask(), pin);
        }
        void write(bool const & state) {
            uint8_t read = ioexp_->read();
            util::write_bit(read, pin, state);
            ioexp_->write(read);
        }
        bool read() {
            if(pm_set_ == false) { //not nice, but the only way...
                pm_set_ = true;
                ioexp_->write(ioexp_->mask());
            }
            uint8_t read = ioexp_->read();
            return util::read_bit(read, pin);
        }
    private:
        device::PCF8574_class * ioexp_;
        bool pm_set_;
    };
    
}//end namespace 

#endif //__PCF8574_HEADER
