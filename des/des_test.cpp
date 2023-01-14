//
// Created by xjh on 2023/1/14.
//


#include <gtest/gtest.h>
#include "des.h"


class DesTest : public ::testing::Test {
};

TEST_F(DesTest, des_encrypt) {
    uint8_t a = 1;
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
    uint8_t keys[][6] = {0};


//    EXPECT_EQ(keys[0], 0xff);
}