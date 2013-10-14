#ifndef USBHELPER_HEADER
#define USBHELPER_HEADER

#include "Arduino.h"
#include <UsbKeyboardMod.h>

void delayMs(unsigned int ms)
{
  for (unsigned int  i = 0; i < ms; i++) {
    delayMicroseconds(1000);
  }
}
void initKeyboard()
{
  TIMSK0&=!(1<<TOIE0);
  cli();
  usbDeviceDisconnect();
  delayMs(250);
  usbDeviceConnect();
  sei();
  
  
  for(int i = 0; i < 150; ++i)
  {
	    UsbKeyboard.update();
		delayMs(10);
  }
}
#endif
