#!/bin/bash 

export OLD_DIR="/usr/bin"
export DIR="/opt/local/bin"
find ./makefile/  -name *.mk | xargs perl -p -i -e 's/$ENV{OLD_DIR}/$ENV{DIR}/g'
