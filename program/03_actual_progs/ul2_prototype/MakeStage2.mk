#---------------------------name----------------------------------------
TARGET = stage2

ARDLIBS = Wire LiquidCrystal UsbKeyboard

MODEL = ATMega20MHz

PORT = /dev/ttyACM*

BAUD = 19200

OPT = s

include /home/msk/ArduinoMin/makefile/Master_Makefile.mk
