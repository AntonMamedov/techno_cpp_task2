cmake_minimum_required(VERSION 3.9.2)
project(multy_thread_test C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -pthread")
add_executable(test main.c)
include_directories(${CMAKE_SOURCE_DIR}/../filemetrics_multithreaded/inc)
target_link_libraries(test PRIVATE ${CMAKE_SOURCE_DIR}/../filemetrics_multithreaded/build/libfilemetrics_shared.so m)