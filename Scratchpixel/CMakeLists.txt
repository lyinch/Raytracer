cmake_minimum_required(VERSION 3.8)
project(Scratchpixel)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Vec3.cpp Vec3.h Matrix.cpp Matrix.h MathUtils.h Ray.h Ray.cpp Vec2.h Object.h Sphere.h Light.h IO.h Triangle.h)
add_executable(Scratchpixel ${SOURCE_FILES})