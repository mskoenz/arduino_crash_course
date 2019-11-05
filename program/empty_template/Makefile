#---------------------------name----------------------------------------
TARGET := $(shell ls | grep *.cpp | sed 's/.\{4\}$$//')

ARDLIBS = 

#~ MODEL = ATMega16MHz
MODEL = ATMega20MHz

#~ PORT ?= /dev/ttyACM*
PORT ?= /dev/ttyUSB*

OPT = 3

include /home/msk/ArduinoMin/makefile/Master_Makefile.mk
