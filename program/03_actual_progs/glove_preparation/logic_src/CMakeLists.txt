cmake_minimum_required (VERSION 2.8)
project(ArduinoQt)

#=================== compiler & flags ===================
SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O3 -pedantic")
#~ SET(CMAKE_EXE_LINKER_FLAGS "-pg")

#=================== set paths ===================
set(SRC "${PROJECT_SOURCE_DIR}/src")

set(LIB logic)

set(MAJOR 0)
set(MINOR 1)

#=================== include directories ===================
include_directories("${SRC}")
include_directories("/home/msk/ArduinoMin/libraries/CustomHeaderLibs")
include_directories("/home/msk/Programmieren/Perimeter/neat_impl/src/addons")

#=================== added subdirs ===================
#~ add_subdirectory("src")
add_subdirectory("examples")
add_subdirectory("lib")
