// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    29.05.2013 18:21:07 EDT
// File:    main.hpp

#ifndef __MAIN_HEADER
#define __MAIN_HEADER

#include <Arduino.h>

#ifdef __I2C_IO_HEADER
program * prog_ptr = NULL;

void receiveEvent(int n) {
    prog_ptr->receive(n);
}
void requestEvent() {
    prog_ptr->request();
}
#endif //__I2C_IO_HEADER

int main(void)
{
    init();
#if defined(USBCON)
    USBDevice.attach();
#endif
    
    program prog;
    
    #ifdef __I2C_IO_HEADER
        prog_ptr = &prog;
    #endif //__I2C_IO_HEADER
    
    for (;;) {
        prog.loop();
        if (serialEventRun) serialEventRun();
    }
    
    return 0;
}
#endif //__MAIN_HEADER

