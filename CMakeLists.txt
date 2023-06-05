cmake_minimum_required(VERSION 3.22)
project(lightweight_block_ciphers)

# dependence
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GoogleTest.cmake)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_executable(lightweight_block_ciphers src/des/des_test.cpp src/des/des.c src/aes/aes.c src/aes/aes.h src/des/des.h src/aes/aes_test.cpp src/midori/midori.c src/midori/midori.h src/midori/midori_test.cpp src/lllwbc/lllwbc.c src/lllwbc/lllwbc.h src/lllwbc/lllwbc_test.cpp src/tools/bit.c src/tools/bit.h src/tools/tools_test.cpp)


target_link_libraries(
        lightweight_block_ciphers
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lightweight_block_ciphers)
