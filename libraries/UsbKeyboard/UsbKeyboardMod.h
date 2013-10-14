/*
 * Based on Obdev's AVRUSB code and under the same license.
 *
 * TODO: Make a proper file header. :-)
 */
#ifndef __UsbKeyboard_h__
#define __UsbKeyboard_h__

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <string.h>

#include "usbdrv.h"

// TODO: Work around Arduino 12 issues better.
//#include <WConstants.h>
//#undef int()

typedef uint8_t byte;


#define BUFFER_SIZE 4 // Minimum of 2: 1 for modifiers + 1 for keystroke 


static uchar    idleRate;           // in 4 ms units 


/* We use a simplifed keyboard report descriptor which does not support the
 * boot protocol. We don't allow setting status LEDs and but we do allow
 * simultaneous key presses. 
 * The report descriptor has been created with usb.org's "HID Descriptor Tool"
 * which can be downloaded from http://www.usb.org/developers/hidpage/.
 * Redundant entries (such as LOGICAL_MINIMUM and USAGE_PAGE) have been omitted
 * for the second INPUT item.
 */
PROGMEM char const usbHidReportDescriptor[35] = { /* USB report descriptor */
  0x05, 0x01,                    // USAGE_PAGE (Generic Desktop) 
  0x09, 0x06,                    // USAGE (Keyboard) 
  (char)0xa1, 0x01,                    // COLLECTION (Application) 
  0x05, 0x07,                    //   USAGE_PAGE (Keyboard) 
  0x19, (char)0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl) 
  0x29, (char)0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI) 
  0x15, 0x00,                    //   LOGICAL_MINIMUM (0) 
  0x25, 0x01,                    //   LOGICAL_MAXIMUM (1) 
  0x75, 0x01,                    //   REPORT_SIZE (1) 
  (char)0x95, 0x08,                    //   REPORT_COUNT (8) 
  (char)0x81, 0x02,                    //   INPUT (Data,Var,Abs) 
  (char)0x95, BUFFER_SIZE-1,           //   REPORT_COUNT (simultaneous keystrokes) 
  0x75, 0x08,                    //   REPORT_SIZE (8) 
  0x25, 0x65,                    //   LOGICAL_MAXIMUM (101) 
  0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated)) 
  0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application) 
  (char)0x81, 0x00,                    //   INPUT (Data,Ary,Abs) 
  (char)0xc0                           // END_COLLECTION 
};



/* Keyboard usage values, see usb.org's HID-usage-tables document, chapter
 * 10 Keyboard/Keypad Page for more codes.
 */

//MOD
//keys are used from device/hid_keys.hpp

class UsbKeyboardDevice {
 public:
  UsbKeyboardDevice () {
    PORTD = 0; // TODO: Only for USB pins?
    DDRD |= ~USBMASK;

    cli();
    usbDeviceDisconnect();
    usbDeviceConnect();


    usbInit();
      
    sei();

    // TODO: Remove the next two lines once we fix
    //       missing first keystroke bug properly.
    memset(reportBuffer, 0, sizeof(reportBuffer));      
    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
  }
    
  void update() {
    usbPoll();
  }
    
    void sendKeyStroke(byte keyStroke) {
        sendKeyStroke(keyStroke, 0);
    }
    void sendKeyStroke(byte keyStroke, byte modifiers) {

        while (!usbInterruptIsReady()) {
            // Note: We wait until we can send keystroke
            //       so we know the previous keystroke was
            //       sent.
        }
        memset(reportBuffer, 0, sizeof(reportBuffer));

        reportBuffer[0] = modifiers;
        reportBuffer[1] = keyStroke;

        usbSetInterrupt(reportBuffer, sizeof(reportBuffer));

        while (!usbInterruptIsReady()) {
            // Note: We wait until we can send keystroke
            //       so we know the previous keystroke was
            //       sent.
        }
        // This stops endlessly repeating keystrokes:
        memset(reportBuffer, 0, sizeof(reportBuffer));
        usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
    }
    void sendBuffer(byte * buffer) {
        memset(reportBuffer, 0, sizeof(reportBuffer));
        
        while (!usbInterruptIsReady()) {} //wait until ready

        for(uint8_t i = 0; i < BUFFER_SIZE; ++i)
            reportBuffer[i] = buffer[i];

        usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
    }
    void clear() {
        while (!usbInterruptIsReady()) {} //wait until ready
        
        // This stops endlessly repeating keystrokes:
        memset(reportBuffer, 0, sizeof(reportBuffer));
        usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
    }
    //private: TODO: Make friend?
    uchar    reportBuffer[4];    // buffer for HID reports [ 1 modifier byte + (len-1) key strokes]
};

UsbKeyboardDevice UsbKeyboard = UsbKeyboardDevice();

#ifdef __cplusplus
extern "C"{
#endif 
    // USB_PUBLIC uchar usbFunctionSetup
    uchar usbFunctionSetup(uchar data[8]) {
        usbRequest_t    *rq = (usbRequest_t *)((void *)data);

        usbMsgPtr = UsbKeyboard.reportBuffer; //
        if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {
            /* class request type */

            if(rq->bRequest == USBRQ_HID_GET_REPORT) {
                /* wValue: ReportType (highbyte), ReportID (lowbyte) */

                /* we only have one report type, so don't look at wValue */
                // TODO: Ensure it's okay not to return anything here?    
                return 0;

            } else if(rq->bRequest == USBRQ_HID_GET_IDLE) {
        //            usbMsgPtr = &idleRate;
        //            return 1;
        return 0;
          }else if(rq->bRequest == USBRQ_HID_SET_IDLE){
        idleRate = rq->wValue.bytes[1];
          }
        } else {
            /* no vendor specific requests implemented */
        }
        return 0;
  }
#ifdef __cplusplus
} // extern "C"
#endif


#endif // __UsbKeyboard_h__
