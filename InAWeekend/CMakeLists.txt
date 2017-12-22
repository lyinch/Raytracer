cmake_minimum_required(VERSION 3.8)
project(InAWeekend)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp vec3.cpp vec3.h ray.h hitable.h sphere.h hitable_list.h camera.h material.h material.h lambertian.h)
add_executable(InAWeekend ${SOURCE_FILES})