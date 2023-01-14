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
    uint64_t plainText = 0x0123456789abcdef;
    uint32_t left = 0;
    uint32_t right = 0;

    ip_permutation(plainText, &left, &right);

    EXPECT_EQ(left, 0xcc00ccff);
    EXPECT_EQ(right, 0xf0aaf0aa);

}

TEST_F(DesTest, pc1_permutation) {
    uint8_t key[] = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
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