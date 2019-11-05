// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.06.2013 20:47:31 EDT
// File:    bridge.hpp

#ifndef __BRIDGE_HEADER
#define __BRIDGE_HEADER

#include <ustd_generic.hpp>
#include <tool/ring_buffer.hpp>

class gesture_class {
    typedef ustd::array<uint8_t, 10> array_type;
    typedef array_type::size_type size_type;
//=================== public ===================
public:
//------------------- ctors -------------------
    gesture_class() {
    }
    template<typename U> //U is a model of the vector concept
    bool contains(U const & val) {
        for(size_type i = 0; i < lower_.size(); ++i) {
            if(val[i] > upper_[i] or val[i] < lower_[i])
                return false;
        }
        return true;
    }
    
    //------------------- print and serialize -------------------
    template<typename S>
    void print(S & os) const {
        os << lower_ << F("-") << upper_;
    }
    template<typename Archive>
    void serialize(Archive & ar) {
        ar & lower_;
        //~ ar & upper_;
    }
//=================== private ===================
//~ private:
    array_type lower_;
    array_type upper_;
};

class bridge_class {
    typedef ustd::static_vector<gesture_class, 30> array_type;
    typedef array_type::size_type size_type;
public:
    //------------------- ctors -------------------
    bridge_class() {
    }
    //------------------- print and serialize -------------------
    template<typename S>
    void print(S & os) const {
        os << gest_;
    }
    template<typename Archive>
    void serialize(Archive & ar) {
        ar & gest_;
    }
private:
    array_type gest_;
    tool::ring_buffer<double, 8> hist_;
    
};

gesture_class vec_;
bridge_class b;

char in;

#endif //__BRIDGE_HEADER
