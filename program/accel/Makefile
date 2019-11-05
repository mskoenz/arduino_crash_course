#---------------------------name----------------------------------------
TARGET := $(shell ls | grep *.cpp | sed 's/.\{4\}$$//')

ARDLIBS = Wire SoftwareSerial

#~ MODEL = ATMega20MHz
#~ PORT ?= /dev/ttyUSB*
#~ BAUD = 57600


MODEL = ATMega16MHz
PORT ?= /dev/ttyACM*
BAUD = 460800

OPT = s

include /home/msk/ArduinoMin/makefile/Master_Makefile.mk
