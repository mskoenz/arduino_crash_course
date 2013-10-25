#---------------------------name----------------------------------------
TARGET := $(shell ls | grep *.cpp | sed 's/.\{4\}$$//')

ARDLIBS = 

MODEL = ATMega16MHz

PORT ?= /dev/ttyACM*

#leave this to O1. Os, O2 and O3 are worse than O1
OPT = 1

include /home/msk/ArduinoMin/makefile/Master_Makefile.mk
