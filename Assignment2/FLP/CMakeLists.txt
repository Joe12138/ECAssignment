cmake_minimum_required(VERSION 3.17)
project(FLP)

set(CMAKE_CXX_STANDARD 14)

add_executable(FLP main.cpp EAMLS.cpp EAMLS.h DataLoader.cpp DataLoader.h BruteForce.cpp BruteForce.h)