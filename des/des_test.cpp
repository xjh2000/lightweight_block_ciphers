//
// Created by xjh on 2023/1/14.
//


#include <gtest/gtest.h>
#include "des.h"


class DesTest : public ::testing::Test {
};

TEST_F(DesTest, des_encrypt) {
    uint8_t plainText[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
    uint8_t cipherText[8] = {0};
    uint8_t cipherText_correct[8] = {0x85, 0xe8, 0x13, 0x54, 0x0f, 0x0a, 0xb4, 0x05,};
    des_encrypt(plainText, key, cipherText);

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(cipherText[i], cipherText_correct[i]);
    }
}

TEST_F(DesTest, des_decrypt) {
    uint8_t plainText[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
    uint8_t cipherText[8] = {0};
    uint8_t decryptText[8] = {0};

    des_encrypt(plainText, key, cipherText);
    des_decrypt(cipherText, key, decryptText);

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(plainText[i], decryptText[i]);
    }
}


TEST_F(DesTest, s_box_change) {

    uint8_t extend[6] = {0x61, 0x17, 0xba, 0x86, 0x65, 0x27};
    uint8_t S[4] = {0};
    uint8_t S_Expect[4] = {0x5c, 0x82, 0xb5, 0x97};
    s_box_change(extend, S);
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(S_Expect[i], S[i]);
    }
}

TEST_F(DesTest, des_turn) {

    uint8_t key_1[6] = {0x1b, 0x02, 0xef, 0xfc, 0x70, 0x72};
    uint8_t left[4] = {0xcc, 0x00, 0xcc, 0xff};
    uint8_t right[4] = {0xf0, 0xaa, 0xf0, 0xaa};
    uint8_t left_expect[4] = {0xef, 0x4a, 0x65, 0x44};
    des_turn(left, right, key_1);

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(left[i], left_expect[i]);
    }


}

TEST_F(DesTest, ip_permutation) {
    uint8_t plainText[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    uint8_t left[4] = {0};
    uint8_t right[4] = {0};
    uint8_t correct_left[4] = {0xcc, 0x00, 0xcc, 0xff};
    uint8_t correct_right[4] = {0xf0, 0xaa, 0xf0, 0xaa};

    ip_permutation(plainText, left, right);

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(left[i], correct_left[i]);
        EXPECT_EQ(right[i], correct_right[i]);
    }


}

TEST_F(DesTest, CD_shift) {
    uint8_t C[4] = {0xf0, 0xcc, 0xaa, 0xf0};
    uint8_t D[4] = {0xf0, 0xcc, 0xaa, 0xf0};

    CD_shift(C, 1);

    EXPECT_EQ(C[0], 0xe1);
    EXPECT_EQ(C[1], 0x99);
    EXPECT_EQ(C[2], 0x55);
    EXPECT_EQ(C[3], 0xf0);
    CD_shift(C, 1);
    CD_shift(D, 2);
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(C[i], D[i]);
    }
}

TEST_F(DesTest, pc1_permutation) {
    uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
    uint8_t C[4] = {0};
    uint8_t D[4] = {0};

    pc1_permutation(key, C, D);

    EXPECT_EQ(C[0], 0xf0);
    EXPECT_EQ(C[1], 0xcc);
    EXPECT_EQ(C[2], 0xaa);
    EXPECT_EQ(C[3], 0xf0);

    EXPECT_EQ(D[0], 0x55);
    EXPECT_EQ(D[1], 0x66);
    EXPECT_EQ(D[2], 0x78);
    EXPECT_EQ(D[3], 0xf0);
}

TEST_F(DesTest, pc2_permutation) {
    uint8_t key[6] = {0};
    uint8_t correct_key[6] = {0x1b, 0x02, 0xef, 0xfc, 0x70, 0x72};
    uint8_t C[4] = {0xe1, 0x99, 0x55, 0xf0};
    uint8_t D[4] = {0xaa, 0xcc, 0xf1, 0xe0};

    pc2_permutation(C, D, key);

    for (int i = 0; i < 6; ++i) {
        EXPECT_EQ(key[i], correct_key[i]);
    }
}


TEST_F(DesTest, generate_keys) {
    uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
    uint8_t keys[16][6] = {{0}};
    uint8_t key_1[6] = {0x1b, 0x02, 0xef, 0xfc, 0x70, 0x72};
    uint8_t key_8[6] = {0xf7, 0x8a, 0x3a, 0xc1, 0x3b, 0xfb};
    uint8_t key_11[6] = {0x21, 0x5f, 0xd3, 0xde, 0xd3, 0x86};
    generate_keys(key, keys);

    for (int i = 0; i < 6; ++i) {
        EXPECT_EQ(keys[0][i], key_1[i]);
        EXPECT_EQ(keys[7][i], key_8[i]);
        EXPECT_EQ(keys[10][i], key_11[i]);
    }
//    EXPECT_EQ(keys[0], 0xff);
}