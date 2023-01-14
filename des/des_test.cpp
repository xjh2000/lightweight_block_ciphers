//
// Created by xjh on 2023/1/14.
//


#include <gtest/gtest.h>
#include "des.h"


class DesTest : public ::testing::Test {
};

TEST_F(DesTest, des_encrypt) {

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


TEST_F(DesTest, generate_keys) {
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t keys[16];

    generate_keys(key, keys);
//    EXPECT_EQ(keys[0], 0xff);
}