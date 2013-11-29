// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    15.11.2013 02:40:53 CET
// File:    light_wrapper.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __LIGHT_WRAPPER_HEADER
#define __LIGHT_WRAPPER_HEADER

#include <Arduino.h>
#include "../ustd/shared_ptr.hpp"

namespace tool{
    namespace detail {
        class light_wrapper_base_class {
        public:
            virtual ~light_wrapper_base_class() {}
        //------------------- supported ops -------------------
            virtual light_wrapper_base_class & operator=(state::light_enum const & in) = 0;
            virtual void update() = 0;
        private:
            
        };

        template<typename T>
        class light_wrapper_derived_class: public light_wrapper_base_class {
        public:
            light_wrapper_derived_class(): val_() {
            }
            explicit light_wrapper_derived_class(T const & t): val_(t) {
            }
        //------------------- supported ops -------------------
            light_wrapper_base_class & operator=(state::light_enum const & in) {
                val_ = in;
                return (*this);
            }
            void update() {
                val_.update();
            }
        private:
            T val_;
        };
    }//end namespace detail

    class light_wrapper_class {
    public:
        light_wrapper_class(): ptr_() {
        }
    //------------------- supported ctors -------------------
        template<typename pin_concept, bool on_state = HIGH>
        light_wrapper_class(tool::light_class<pin_concept, on_state> const & t): ptr_(new detail::light_wrapper_derived_class<tool::light_class<pin_concept, on_state>>(t)) {
        }
    //------------------- supported operations -------------------
        light_wrapper_class & operator=(state::light_enum const & in) {
            ASSERT(ptr_ != NULL)
            ptr_->operator=(in);
            return (*this);
        }
        void update() {
            ASSERT(ptr_ != NULL)
            ptr_->update();
        }
    private:
        ustd::shared_ptr<detail::light_wrapper_base_class> ptr_;
    };
}//end namespace tool

#endif //__LIGHT_WRAPPER_HEADER
