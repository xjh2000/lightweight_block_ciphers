cmake_minimum_required(VERSION 3.22)
project(lightweight_block_ciphers)

# dependence
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GoogleTest.cmake)

set(CMAKE_CXX_STANDARD 14)

include_directories(des)

enable_testing()

add_executable(lightweight_block_ciphers des/des_test.cpp des/des.cpp)


target_link_libraries(
        lightweight_block_ciphers
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lightweight_block_ciphers)
