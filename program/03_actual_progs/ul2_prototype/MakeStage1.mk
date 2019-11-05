#---------------------------name----------------------------------------
TARGET = stage1

ARDLIBS = Wire

MODEL = ATMega20MHz

PORT = /dev/ttyACM*

OPT = s

include /home/msk/ArduinoMin/makefile/Master_Makefile.mk
