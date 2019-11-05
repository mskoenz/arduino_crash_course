#---------------------------name----------------------------------------
TARGET := $(shell ls | grep *.cpp | sed 's/.\{4\}$$//')

ARDLIBS = Wire SoftwareSerial Servo



# MODEL = ATMega20MHz
MODEL = ATMega16MHz
PORT ?= /dev/tty.usbserial-144210
# PORT ?= /dev/tty.usbmodem1442301
BAUD = 230400
# BAUD = 460800

OPT = s

include /Users/mskoenz/programming/hobby/arduino/ArduinoMin/makefile/Master_Makefile.mk
