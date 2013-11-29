// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    14.11.2013 00:38:16 CET
// File:    shared_ptr.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __SHARED_PTR_HEADER
#define __SHARED_PTR_HEADER

namespace ustd {
    template<typename T>
    class shared_ptr {
        void incr() {
            ++(*count_);
        }
        void decr() {
            --(*count_);
        }
    public:
        typedef T element_type;
        
    //------------------- ctor -------------------
        explicit shared_ptr(T * ptr = NULL): ptr_(ptr) {
            count_ = new uint8_t(0);
            ASSERT(count_ != NULL)
            incr();
        }
        shared_ptr(shared_ptr const & rhs): ptr_(rhs.ptr_), count_(rhs.count_) {
            incr();
        }
    //------------------- dtor -------------------
        ~shared_ptr() {
            if(ptr_ == NULL) {
                decr();
                return;
            }
            if(*count_ == 1) {
                delete ptr_;
                delete count_;
            } else {
                ptr_ = NULL;
                decr();
            }
        }
    //------------------- assign -------------------
        shared_ptr & operator=(shared_ptr const & rhs) {
            if(ptr_ != rhs.ptr_) {
                if(ptr_ != NULL) {
                    if(*count_ == 1) {
                        delete ptr_;
                        delete count_;
                    }
                    else
                        decr();
                }
                
                ptr_ = rhs.ptr_;
                count_ = rhs.count_;
                incr();
            }
            return (*this);
        }
    //------------------- deref -------------------
        element_type * operator->() const {
            return ptr_;
        }
        element_type & operator*() const {
            return *ptr_;
        }
    //------------------- compare -------------------
        //~ bool operator==(T * ptr) const {
            //~ return  ptr == ptr_;
        //~ }
        //~ bool operator==(shared_ptr const & arg) const {
            //~ return  arg.prt_ == ptr_;
        //~ }
        bool operator!=(T * ptr) const {
            return ptr != ptr_;
        }
        bool operator!=(shared_ptr const & arg) const {
            return  arg.prt_ != ptr_;
        }
    private:
        element_type * ptr_;
        uint8_t * count_;
    };
}//end namespace ustd
#endif //__SHARED_PTR_HEADER
