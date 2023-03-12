//
// Created by 93462 on 2023/3/8.
//
#include <gtest/gtest.h>
#include "aes.h"

class AesTest : public ::testing::Test {
};

TEST_F(AesTest, aes_key_expand) {
    uint8_t key[16] = {
            0x2b, 0x7e, 0x15, 0x16,
            0x28, 0xae, 0xd2, 0xa6,
            0xab, 0xf7, 0x15, 0x88,
            0x09, 0xcf, 0x4f, 0x3c,
    };
    uint8_t keys[176] = {0};
    uint8_t multipleOf4[4] = {
            0xa0, 0xfa, 0xfe, 0x17
    };
    uint8_t noMultipleOf4[4] = {
            0x88, 0x54, 0x2c, 0xb1
    };

    aes_key_expand(key, keys);

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(multipleOf4[i], keys[16 + i]);
        EXPECT_EQ(noMultipleOf4[i], keys[20 + i]);
    }
}