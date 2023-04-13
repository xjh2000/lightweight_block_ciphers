//
// Created by 93462 on 2023/4/12.
//

#include "midori.h"
#include "gtest/gtest.h"

class MidoriTest : public ::testing::Test {
};


TEST_F(MidoriTest, midori_encrypt) {
    uint8_t plainText[16] = {0};
    uint8_t key[16] = {0};
    uint8_t cipherText[16] = {0};
    uint8_t expect_cipherText[16] = {0xc0, 0x55, 0xcb, 0xb9, 0x59, 0x96, 0xd1, 0x49, 0x02, 0xb6, 0x05, 0x74, 0xd5, 0xe7,
                                     0x28, 0xd6};
    midori_encrypt(plainText, key, cipherText);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(cipherText[i], expect_cipherText[i]);
    }
}

TEST_F(MidoriTest, midori_shuffle_cell) {
    uint8_t state[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8_t expect_state[16] = {0, 10, 5, 15, 14, 4, 11, 1, 9, 3, 12, 6, 7, 13, 2, 8};
    midori_shuffle_cell(state);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(state[i], expect_state[i]);
    }
}

TEST_F(MidoriTest, midori_mix_column) {
    uint8_t state[16] = {1, 2, 3, 4, 4, 3, 2, 1, 9, 8, 7, 6, 6, 7, 8, 9};
    uint8_t expect_state[16] = {5, 6, 7, 0, 0, 7, 6, 5, 9, 8, 7, 6, 6, 7, 8, 9};
    midori_mix_column(state);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(state[i], expect_state[i]);
    }
}

TEST_F(MidoriTest, midori_sub_cell) {
    uint8_t state[16] = {1,2,3,4,
                         1,2,3,4,
                         1,2,3,4,
                         1,2,3,4,};
    uint8_t expect_state[16] = {16, 75, 67, 162,
                                16, 75, 67, 162,
                                16, 75, 67, 162,
                                16, 75, 67, 162, };
    midori_sub_cell(state);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(state[i], expect_state[i]);
    }
}

TEST_F(MidoriTest, midori_sp) {
    uint8_t array[6] = {0x11, 0xc2, 0x84, 0x38, 0xdc, 0xf1};
    uint8_t expect_array[6] = {0x11, 0xc2, 0x84, 0x38, 0xdc, 0xf1};
    for (int i = 0; i < 6; ++i) {
        midori_sp1(&array[i]);
        midori_inv_sp1(&array[i]);
        EXPECT_EQ(array[i], expect_array[i]);
    }

    for (int i = 0; i < 6; ++i) {
        midori_sp2(&array[i]);
        midori_inv_sp2(&array[i]);
        EXPECT_EQ(array[i], expect_array[i]);
    }

    for (int i = 0; i < 6; ++i) {
        midori_sp3(&array[i]);
        midori_inv_sp3(&array[i]);
        EXPECT_EQ(array[i], expect_array[i]);
    }

    for (int i = 0; i < 6; ++i) {
        midori_sp4(&array[i]);
        midori_inv_sp4(&array[i]);
        EXPECT_EQ(array[i], expect_array[i]);
    }

}

TEST_F(MidoriTest, midori_key_generation) {
    uint8_t key[16] = {0};

    uint8_t round_keys[304] = {0};
    uint8_t expect_round_keys[304] = {
            0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
            1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1,
            0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1,
            0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1,
            1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0,
            0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0,
            1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
            0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0,
            0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1,
            0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0,
            0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0,
            1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0,
            0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
            0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0,
            0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0};

    midori_key_generation(key, round_keys);

    for (int i = 0; i < 304; ++i) {
        EXPECT_EQ(expect_round_keys[i], round_keys[i]);
    }
}