// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    13.06.2013 18:45:18 EDT
// File:    meta_template.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __META_TEMPLATE_HEADER
#define __META_TEMPLATE_HEADER

//=================== meta_if ===================
template<bool cond, typename T, typename F> //default true
struct m_if {
    typedef T type;
};
//------------------- partial specialsiation for true -------------------
template<typename T, typename F>
struct m_if<false, T, F> {
    typedef F type;
};
//------------------- mtp stuff -------------------
template<typename T>
struct is_const {
    enum{value = 0};
};
template<typename T>
struct is_const<T const> {
    enum{value = 1};
};

template<typename T>
struct is_class {
    template<typename U> static char check(void(U::*)(void));
    template<typename U> static double check(...);
    
    enum { value = (sizeof(char) == sizeof(check<T>(0))) };
};

template<typename T>
struct is_array {
    static T t;
    
    template<int N> struct wrap {typedef char type;};
    template<typename U> static U * ptr(U u[]);
    template<typename U> static U ptr(U u);
    
    template<typename U> static typename wrap<sizeof(t = ptr(t))>::type check(int);
    template<typename U> static double check(...);
    
    enum{value = (sizeof(double) == sizeof(check<T>(int())))};
};
template<typename T> //remove constness before doing array checks since const i = j is also illegal
struct is_array<T const > {
    enum{value = is_array<T>::value};
};

//------------------- dis/enable_if -------------------
template<bool b, typename T>
struct enable_if {
};
template<typename T>
struct enable_if<true, T> {
    typedef T type;
};
template<bool b, typename T>
struct disable_if {
};
template<typename T>
struct disable_if<false, T> {
    typedef T type;
};
//------------------- is_same -------------------
template<typename T, typename U>
struct is_same {
    enum {value = false};
};
template<typename T>
struct is_same<T, T> {
    enum {value = true};
};


#endif //__META_TEMPLATE_HEADER
