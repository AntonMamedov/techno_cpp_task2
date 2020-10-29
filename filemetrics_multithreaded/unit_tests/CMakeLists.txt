project(unit_tests)
add_subdirectory(${CMAKE_SOURCE_DIR}/../googletest build)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(Google_Tests_run str_tests.cpp str_map_tests.cpp vec_tests.cpp
        tf_idf_priority_queue_tests.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)