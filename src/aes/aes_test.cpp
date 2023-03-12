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


TEST_F(AesTest, aes_shift_row) {
    uint8_t text[16] = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
    };

    uint8_t shift_row_text[16] = {
            1, 6, 11, 16,
            5, 10, 15, 4,
            9, 14, 3, 8,
            13, 2, 7, 12
    };

    aes_shift_row(text);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(text[i], shift_row_text[i]);
    }
}


TEST_F(AesTest, aes_mix_columns) {
    uint8_t text[16] = {
            0xd4, 0xbf, 0x5d, 0x30,
            0xe0, 0xb4, 0x52, 0xae,
            0xb8, 0x41, 0x11, 0xf1,
            0x1e, 0x27, 0x98, 0xe5,
    };

    uint8_t mix_columns_text[16] = {0};
    uint8_t expect_mix_columns_text[16] = {
            0x04, 0x66, 0x81, 0xe5,
            0xe0, 0xcb, 0x19, 0x9a,
            0x48, 0xf8, 0xd3, 0x7a,
            0x28, 0x06, 0x26, 0x4c,
    };


    aes_mix_columns(text, mix_columns_text);

    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(expect_mix_columns_text[i], mix_columns_text[i]);
    }
}