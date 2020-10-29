cmake_minimum_required(VERSION 3.9.2)
project(filemetrics C)


set(CMAKE_C_STANDARD 11)
include_directories(inc)
file(GLOB C_SOURCES "src/*.c")
add_library(filemetrics STATIC ${C_SOURCES})
add_library(filemetrics_shared SHARED ${C_SOURCES})
target_link_libraries(filemetrics m)
add_subdirectory(unit_tests)