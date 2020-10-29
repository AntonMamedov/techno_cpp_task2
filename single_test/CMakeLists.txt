cmake_minimum_required(VERSION 3.9.2)
project(single_test C)

set(CMAKE_C_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/../filemetrics/inc)
add_executable(single_test main.c)
target_link_libraries(single_test PRIVATE ${CMAKE_SOURCE_DIR}/../filemetrics/build/libfilemetrics_shared.so m)