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

TEST_F(AesTest, aes_inv_shift_row) {
    uint8_t text[16] = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
    };
    uint8_t text1[16] = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
    };
    aes_shift_row(text);
    aes_inv_shift_row(text);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(text[i], text1[i]);
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

TEST_F(AesTest, aes_encrypt) {
    // 6b c1 be e2 [0-3]
    // 2e 40 9f 96 [4-7]
    // e9 3d 7e 11 [8-11]
    // 73 93 17 2a [12-15]
    uint8_t plainText[16] = {
            0x6b, 0xc1, 0xbe, 0xe2,
            0x2e, 0x40, 0x9f, 0x96,
            0xe9, 0x3d, 0x7e, 0x11,
            0x73, 0x93, 0x17, 0x2a,
    };
    // 2b 7e 15 16
    // 28 ae d2 a6
    // ab f7 15 88
    // 09 cf 4f 3c
    uint8_t key[16] = {
            0x2b, 0x7e, 0x15, 0x16,
            0x28, 0xae, 0xd2, 0xa6,
            0xab, 0xf7, 0x15, 0x88,
            0x09, 0xcf, 0x4f, 0x3c,
    };
    uint8_t cipherText[16] = {0};

    // 3a d7 7b b4
    // 0d 7a 36 60
    // a8 9e ca f3
    // 24 66 ef 97
    uint8_t expect_cipherText[16] = {
            0x3a, 0xd7, 0x7b, 0xb4,
            0x0d, 0x7a, 0x36, 0x60,
            0xa8, 0x9e, 0xca, 0xf3,
            0x24, 0x66, 0xef, 0x97,
    };


    aes_encrypt(plainText, key, cipherText);

    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(expect_cipherText[i], cipherText[i]);
    }
}