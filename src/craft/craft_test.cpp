//
// Created by xjh on 2023/7/28.
//
#include "craft.h"
#include "gtest/gtest.h"

class CraftTest : public ::testing::Test {
};


TEST_F(CraftTest, craft) {

    int Tweak[16] = {
            0x5, 0x4, 0xc, 0xd, 0x9, 0x4, 0xf, 0xf, 0xd, 0x0, 0x6, 0x7, 0x0, 0xa, 0x5, 0x8
    };

    int inputText[16] = {
            0x5, 0x7, 0x3, 0x4, 0xf, 0x0, 0x0, 0x6, 0xd, 0x8, 0xd, 0x8, 0x8, 0xa, 0x3, 0xe
    };

    int Key[2][16] = {
            {0x2, 0x7, 0xa, 0x6, 0x7, 0x8, 0x1, 0xa, 0x4, 0x3, 0xf, 0x3, 0x6, 0x4, 0xb, 0xc},
            {0x9, 0x1, 0x6, 0x7, 0x0, 0x8, 0xd, 0x5, 0xf, 0xb, 0xb, 0x5, 0xa, 0xe, 0xf, 0xe}
    };
    int outputText[16] = {0};
    int expect_output_text[16] = {0xa, 0x1, 0x7, 0xd, 0x6, 0xb, 0xd, 0x4, 0xb, 0xe, 0xe, 0xb, 0x9, 0x9, 0x6, 0xf};
    craft(inputText, outputText, Key, Tweak, false);

    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(expect_output_text[i], outputText[i]);
    }
}

TEST_F(CraftTest, craft_decrypt) {

    int Tweak[16] = {
            0x5, 0x4, 0xc, 0xd, 0x9, 0x4, 0xf, 0xf, 0xd, 0x0, 0x6, 0x7, 0x0, 0xa, 0x5, 0x8
    };

    int inputText[16] = {
            0x5, 0x7, 0x3, 0x4, 0xf, 0x0, 0x0, 0x6, 0xd, 0x8, 0xd, 0x8, 0x8, 0xa, 0x3, 0xe
    };

    int Key[2][16] = {
            {0x2, 0x7, 0xa, 0x6, 0x7, 0x8, 0x1, 0xa, 0x4, 0x3, 0xf, 0x3, 0x6, 0x4, 0xb, 0xc},
            {0x9, 0x1, 0x6, 0x7, 0x0, 0x8, 0xd, 0x5, 0xf, 0xb, 0xb, 0x5, 0xa, 0xe, 0xf, 0xe}
    };
    int tempText[16] = {0};
    int outputText[16] = {0};
    int expect_output_text[16] = {0xa, 0x1, 0x7, 0xd, 0x6, 0xb, 0xd, 0x4, 0xb, 0xe, 0xe, 0xb, 0x9, 0x9, 0x6, 0xf};
    craft(inputText, tempText, Key, Tweak, false);
    craft(tempText, outputText, Key, Tweak, true);

    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(inputText[i], outputText[i]);
    }
}


