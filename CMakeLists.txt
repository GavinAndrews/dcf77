cmake_minimum_required(VERSION 3.2)
project(dcf77)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    dcf77.cpp
    dcf77.h)

add_executable(dcf77 ${SOURCE_FILES})