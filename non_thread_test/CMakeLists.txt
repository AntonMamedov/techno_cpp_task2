cmake_minimum_required(VERSION 3.9.2)
project(non_thread_test C)

set(CMAKE_C_STANDARD 11)
add_executable(test_single main.c)
include_directories(${CMAKE_SOURCE_DIR}/../filemetrics/inc)
target_link_libraries(test_single PRIVATE ${CMAKE_SOURCE_DIR}/../filemetrics/build/libfilemetrics.a m)