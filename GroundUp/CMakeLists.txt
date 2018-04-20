cmake_minimum_required(VERSION 3.8)
project(GroundUp)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Ray.cpp Ray.h)
add_executable(GroundUp ${SOURCE_FILES})