cmake_minimum_required(VERSION 3.9.2)
project(multi_test C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -pthread")
include_directories(${CMAKE_SOURCE_DIR}/../filemetrics_multithreaded/inc)
add_executable(multi_test main.c)
target_link_libraries(multi_test PRIVATE ${CMAKE_SOURCE_DIR}/../filemetrics_multithreaded/build/libfilemetrics.a m)