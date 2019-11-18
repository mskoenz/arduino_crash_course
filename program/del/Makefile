#---------------------------name----------------------------------------
TARGET := $(shell ls | grep *.cpp | sed 's/.\{4\}$$//')

ARDLIBS = Wire SoftwareSerial Servo MemoryFree ArduinoSTL

#~ MODEL = ATMega20MHz
#~ PORT ?= /dev/ttyUSB*
#~ BAUD = 57600


MODEL = ATMega16MHz
PORT ?= /dev/tty.usb*
BAUD = 230400

OPT = 3

include /Users/mskoenz/programming/hobby/arduino/ArduinoMin/makefile/Master_Makefile.mk
