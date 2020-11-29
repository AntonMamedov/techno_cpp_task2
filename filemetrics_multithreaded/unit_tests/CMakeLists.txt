project(unit_tests)
add_subdirectory(googletest)
set(CMAKE_CXX_STANDARD 17)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(Google_Tests_run str_tests.cpp str_map_tests.cpp vec_tests.cpp
        tf_idf_priority_queue_tests.cpp hash_map.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)