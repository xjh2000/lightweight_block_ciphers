//
// Created by 93462 on 2023/5/10.
//
#include "llwbc.h"
#include "gtest/gtest.h"
#include "../tools/bit.h"

class LlwbcTest : public ::testing::Test {
};

TEST_F(LlwbcTest, llwbc_key_schedule) {
    uint8_t key[16] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
                       0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,};
    uint8_t kws[2][8] = {0};


    uint8_t kws_expect[2][8] = {{0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,},
                                {0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,}};
    uint8_t krs[21][4] = {0};
    uint8_t krs_except[21][4] = {
            {0x13, 0x19, 0x8a, 0x2e},
            {0x03, 0x70, 0x73, 0x44},
            {0xa4, 0x09, 0x38, 0x22},
            {0x29, 0x9f, 0x31, 0xd0},
            {0x08, 0x2e, 0xfa, 0x98},
            {0xec, 0x4e, 0x6c, 0x89},
            {0x45, 0x28, 0x21, 0xe6},
            {0x38, 0xd0, 0x13, 0x77},
            {0xbe, 0x54, 0x66, 0xcf},
            {0x34, 0xe9, 0x0c, 0x6c},
            {0xc9, 0x7c, 0x50, 0xdd},
            {0xf4, 0x45, 0x25, 0xdb},
            {0xbe, 0x54, 0x66, 0xcf},
            {0xf8, 0x7c, 0x3a, 0xc0},
            {0x45, 0x28, 0x21, 0xe6},
            {0x2c, 0xe2, 0x45, 0x3e},
            {0x08, 0x2e, 0xfa, 0x98},
            {0xe9, 0x33, 0x18, 0x67},
            {0xa4, 0x09, 0x38, 0x22},
            {0xc3, 0xdc, 0x5a, 0xf3},
            {0x13, 0x19, 0x8a, 0x2e},
    };

    bool keyB[128];
    bool kwsB[2][64];
    bool krsB[21][32];

    for (int i = 0; i < 16; ++i) {
        byte_to_bit(key[i], keyB + (i * 8));
    }

    llwbc_key_schedule(keyB, kwsB, krsB);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 8; ++j) {
            bit_to_byte(kwsB[i] + (j * 8), kws[i] + j);
        }
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 8; ++j) {
            EXPECT_EQ(kws_expect[i][j], kws[i][j]);
        }
    }

    for (int i = 0; i < 21; ++i) {
        for (int j = 0; j < 4; ++j) {
            bit_to_byte(krsB[i] + (j * 8), krs[i] + j);
        }
    }
    for (int i = 0; i < 21; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(krs[i][j], krs_except[i][j] ^ 0x11);
        }
    }


}

TEST_F(LlwbcTest, llwbc_f) {
    uint8_t state = 0x45;
    uint8_t state_expect = 0xb9;
    bool stateB[8];
    byte_to_bit(state, stateB);
    llwbc_f(stateB);
    bit_to_byte(stateB, &state);
    EXPECT_EQ(state, state_expect);
}

TEST_F(LlwbcTest, llwbc_p) {
    // (0,1,.....15) -> (6,11,0,12,10,7,13,1,3,15,4,9,2,14,5,8)
    uint8_t state[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    uint8_t state_except[8] = {0x6b, 0x0c, 0xa7, 0xd1, 0x3f, 0x49, 0x2e, 0x58};
    bool stateB[64];
    for (int i = 0; i < 8; ++i) {
        byte_to_bit(state[i], stateB + (i * 8));
    }

    llwbc_p(stateB);

    for (int i = 0; i < 8; ++i) {
        bit_to_byte(stateB + (i * 8), state + i);
    }

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(state_except[i], state[i]);
    }
}

TEST_F(LlwbcTest, llwbc_p_inverse) {
    // (0,1,.....15) -> (2,7,12,8,10,14,0,5,15,11,4,1,3,6,13,9)
    uint8_t state[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    uint8_t state_except[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    bool stateB[64];
    for (int i = 0; i < 8; ++i) {
        byte_to_bit(state[i], stateB + (i * 8));
    }

    llwbc_p(stateB);
    llwbc_p_inverse(stateB);

    for (int i = 0; i < 8; ++i) {
        bit_to_byte(stateB + (i * 8), state + i);
    }

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(state_except[i], state[i]);
    }
}

TEST_F(LlwbcTest, llwbc_encrypt) {
    // PlainText : 01 23 45 67 89 ab cd ef
    // Key : 01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10
    // CipherText : 4d ac 97 75 8b 96 f3 83
    uint8_t plain_text[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    bool plain_textB[64] = {0};
    uint8_t key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
    bool keyB[128] = {0};
    uint8_t cipher_text[8] = {0};
    bool cipher_textB[64] = {0};
    uint8_t cipher_text_expect[8] = {0x4d, 0xac, 0x97, 0x75, 0x8b, 0x96, 0xf3, 0x83};

    for (int i = 0; i < 8; ++i) {
        byte_to_bit(plain_text[i], plain_textB + (i * 8));
    }
    for (int i = 0; i < 16; ++i) {
        byte_to_bit(key[i], keyB + (i * 8));
    }
    llwbc_encrypt(plain_textB, keyB, cipher_textB);

    for (int i = 0; i < 8; ++i) {
        bit_to_byte(cipher_textB + (i * 8), cipher_text + i);
    }

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(cipher_text_expect[i], cipher_text[i]);
    }
}