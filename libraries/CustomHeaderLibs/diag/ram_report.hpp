// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    25.05.2013 19:22:02 EDT
// File:    ram_report.hpp

/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ or COPYING for more details. */

#ifndef __RAM_REPORT_HEADER
#define __RAM_REPORT_HEADER

#include <ustd/iostream.hpp>

extern int    __data_start
            , __data_end
            , __bss_start
            , __bss_end
            , __heap_start
            , __brkval
            , __flp
            ;

namespace diag {
    int ram_capacity() {
        return (RAMEND - int(&__data_start));
    }
    int free_ram() {
        int v;
        return (int) &v - (int(__brkval) == 0 ? int(&__heap_start) : int(__brkval));
    }
    void print_stack() {
        
        int16_t freeptr = __flp;
        int16_t pos = int16_t(&__heap_start);
        int16_t end = int16_t(__brkval);
        
        ustd::cout << GREEN << "used heap: " << GREENB << end - pos << ustd::endl(2);
        
        uint16_t size = 0;
        ustd::cout << ustd::setfill('0');
        for(; pos < end; ++pos) {
            if(size == 0) {
                if(pos == freeptr) {
                    ustd::cout << YELLOW;
                    freeptr = *(uint8_t*)(pos + 2) + (*(uint8_t*)(pos + 3) << 8);
                } else
                    ustd::cout << NONE;
                
                size = *(uint8_t*)pos + (*(uint8_t*)(pos + 1) << 8);
                ustd::cout << "size: " << ustd::setw(3) << size << "  ";
                pos += 2;
            }
            ustd::cout << ustd::setw(3) << *(uint8_t*)pos << " ";
            
            size--;
            if(size == 0)
                ustd::cout << ustd::endl;
        }
        ustd::cout << ustd::endl(2);
    }
    int used_ram() {
        return ram_capacity() - free_ram();
    }
    void ram_report() {
        uint8_t split = 32;
        uint8_t incr = 8;
        uint8_t count = 0;
        
        ustd::cout << F("======= RAM Report =======================================") << ustd::endl;
        
        for(int i = int(&__data_start); i < RAMEND; i += incr) {
            if(i < int(&__data_end))
                ustd::cout << YELLOWB << F("|");
            else if(i < int(&__bss_end))
                ustd::cout << REDB << F("|");
            else if(i < int(__brkval))
                ustd::cout << WHITEB << F("|");
            else if(i < int(SP))
                ustd::cout << GREEN << F(".");
            else if(i < RAMEND)
                ustd::cout << BLUEB << F("|");
            
            if((i - int(&__data_start) + incr) % (split * incr) == 0) {
                ustd::cout << NONE << "  ";
                #define PRINT_RAM(var, color) \
                ustd::cout << color << ustd::setw(6) << F(#var) << F(": ") << ustd::setw(4) << var \
                           << F(" bytes (") << ustd::setw(2) << int(var * 100.0 / 2047 + 0.5) << F("%)");
                //ram_capacity()
                if(count == 1) {
                    uint16_t const data = int(&__data_end) - int(&__data_start);
                    PRINT_RAM(data, YELLOWB)
                } else if(count == 2) {
                    uint16_t const bss = int(&__bss_end) - int(&__bss_start);
                    PRINT_RAM(bss, REDB)
                } else if(count == 3) {
                    uint16_t const heap = int(__brkval) - int(&__heap_start);
                    PRINT_RAM(heap, WHITEB)
                } else if(count == 4) {
                    uint16_t const free = SP - int(__brkval);
                    PRINT_RAM(free, GREENB)
                } else if(count == 5) {
                    uint16_t stack = RAMEND - SP;
                    PRINT_RAM(stack, BLUEB)
                }
                
                ustd::cout << NONE << ustd::endl;
                ++count;
            }
        }
        ustd::cout << F("==========================================================") << ustd::endl;
    }
}//end namespace diag
#endif //__ram_REPORT_HEADER
