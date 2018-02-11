cmake_minimum_required(VERSION 3.8)

project(InOneWeekend)

set(CMAKE_CXX_STANDARD 11)

find_package (Threads)

find_package (OpenGL REQUIRED)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})



find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp vec3.h ray.h hitable.h sphere.h hitable_list.h camera.h shader.h window.h)

add_executable(InOneWeekend ${SOURCE_FILES})
target_link_libraries(InOneWeekend ${GLFW_STATIC_LIBRARIES} "-framework OpenGL")

configure_file(shader.frag shader.frag COPYONLY)
configure_file(shader.vert shader.vert COPYONLY)