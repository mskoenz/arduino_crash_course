// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    07.11.2013 21:42:45 CET
// File:    has_i2c_read_write.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __HAS_I2C_READ_WRITE_HEADER
#define __HAS_I2C_READ_WRITE_HEADER

namespace util {
    //------------------- checks if T is a class and has a method called i2c_read -------------------
    template<typename T, bool is_a_class> 
    struct has_i2c_read_impl {
        
        template<void(T::*)(int)> struct helper {typedef char type;};
        
        template<typename U> static char check(typename helper<&U::i2c_read>::type);
        template<typename U> static double check(...);
        
        enum { value = (sizeof(char) == sizeof(check<T>(0))) };
    };
    template<typename T> 
    struct has_i2c_read_impl<T, false> { //if T is not a class it cannot have print
        enum { value = false };
    };
    template<typename T> 
    struct has_i2c_read {
        enum { value = has_i2c_read_impl<T, ustd::is_class<T>::value>::value };
    };
    //------------------- checks if T is a class and has a method called i2c_write -------------------
    template<typename T, bool is_a_class> 
    struct has_i2c_write_impl {
        
        template<void(T::*)()> struct helper {typedef char type;};
        
        template<typename U> static char check(typename helper<&U::i2c_write>::type);
        template<typename U> static double check(...);
        
        enum { value = (sizeof(char) == sizeof(check<T>(0))) };
    };
    template<typename T> 
    struct has_i2c_write_impl<T, false> { //if T is not a class it cannot have print
        enum { value = false };
    };
    template<typename T> 
    struct has_i2c_write {
        enum { value = has_i2c_write_impl<T, ustd::is_class<T>::value>::value };
    };
}//end namespace util

#endif //__HAS_I2C_READ_WRITE_HEADER
