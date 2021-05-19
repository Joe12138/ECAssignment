cmake_minimum_required(VERSION 3.19)
project(CEC2021)

set(CMAKE_CXX_STANDARD 14)

add_executable(CEC2021 main.cpp cec2013.cpp cec2013.h cfunction.cpp cfunction.h plots.cpp rand2.c rand2.h sortidx.h)