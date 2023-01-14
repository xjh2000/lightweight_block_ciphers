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
    uint64_t key = 0x133457799BBCDFF1;
    uint32_t left = 0;
    uint32_t right = 0;

    pc1_permutation(key, &left, &right);

    EXPECT_EQ(left, 0xf0ccaaf);
    EXPECT_EQ(right, 0x556678f);
}


TEST_F(DesTest, generate_keys) {
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t keys[16];

    generate_keys(key, keys);
    EXPECT_EQ(keys[0], 0xff);
}