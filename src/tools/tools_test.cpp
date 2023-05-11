//
// Created by 93462 on 2023/5/10.
//
#include "bit.h"
#include "gtest/gtest.h"

class ToolTest : public ::testing::Test {
};


TEST_F(ToolTest, bit_to_byte) {
    bool bits[8] = {1, 1, 1, 1, 0, 0, 0, 0};
    uint8_t byte = {0};

    bit_to_byte(bits, &byte);
    EXPECT_EQ(byte, 0xf0);


    bool bits1[8] = {0, 1, 0, 1, 1, 0, 0, 0};
    bit_to_byte(bits1, &byte);

    EXPECT_EQ(byte, 0x58);
}

TEST_F(ToolTest, byte_to_bit) {
    bool bits[8] = {1, 1, 1, 1, 0, 0, 0, 0};
    bool bits1[8] = {0};
    uint8_t byte = {0};

    bit_to_byte(bits, &byte);
    byte_to_bit(byte, bits1);
    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(bits[i], bits1[i]);
    }
}

TEST_F(ToolTest, byte_to_byte) {

    uint8_t str1[8] = {0x11, 0x22, 0x44, 0x55, 0x11, 0x22, 0x44, 0x55};
    uint8_t str2[8] = {0};
    bool temp[64];
    for (int i = 0; i < 8; ++i) {
        byte_to_bit(str1[i], temp + (i * 8));
    }
    for (int i = 0; i < 8; ++i) {
        bit_to_byte(temp + (i * 8), &str2[i]);
    }
    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(str1[i], str2[i]);
    }
}