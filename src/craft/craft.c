
#include <stdio.h>
#include "craft.h"

//
// Created by xjh on 2023/7/28.
//
const int S[16] = {0xc, 0xa, 0xd, 0x3, 0xe, 0xb, 0xf, 0x7, 0x8, 0x9, 0x1, 0x5, 0x0, 0x2, 0x4, 0x6};
const int P[16] = {0xf, 0xc, 0xd, 0xe, 0xa, 0x9, 0x8, 0xb, 0x6, 0x5, 0x4, 0x7, 0x1, 0x2, 0x3, 0x0};
const int Q[16] = {0xc, 0xa, 0xf, 0x5, 0xe, 0x8, 0x9, 0x2, 0xb, 0x3, 0x7, 0x4, 0x6, 0x0, 0x1, 0xd};

const int RC3[32] = {
        0x1, 0x4, 0x2, 0x5, 0x6, 0x7, 0x3, 0x1, 0x4, 0x2, 0x5, 0x6, 0x7, 0x3, 0x1, 0x4,
        0x2, 0x5, 0x6, 0x7, 0x3, 0x1, 0x4, 0x2, 0x5, 0x6, 0x7, 0x3, 0x1, 0x4, 0x2, 0x5
};

const int RC4[32] = {
        0x1, 0x8, 0x4, 0x2, 0x9, 0xc, 0x6, 0xb, 0x5, 0xa, 0xd, 0xe, 0xf, 0x7, 0x3, 0x1,
        0x8, 0x4, 0x2, 0x9, 0xc, 0x6, 0xb, 0x5, 0xa, 0xd, 0xe, 0xf, 0x7, 0x3, 0x1, 0x8
};


void craft_initialize_key(int Key[2][16], int Tweak[16], int dec, int TK[4][16]) {
    for (int i = 0; i < 16; i++) {
        TK[0][i] = Key[0][i] ^ Tweak[i];
        TK[1][i] = Key[1][i] ^ Tweak[i];
        TK[2][i] = Key[0][i] ^ Tweak[Q[i]];
        TK[3][i] = Key[1][i] ^ Tweak[Q[i]];
    }

    if (dec)
        for (int j = 0; j < 4; j++)
            for (int i = 0; i < 4; i++) {
                TK[j][i] ^= (TK[j][i + 8] ^ TK[j][i + 12]);
                TK[j][i + 4] ^= TK[j][i + 12];
            }
}

void craft_round(int Stt[16], int TK[4][16], int r, bool dec) {
    for (int i = 0; i < 4; i++) {
        // MixColumn
        Stt[i] ^= (Stt[i + 8] ^ Stt[i + 12]);
        Stt[i + 4] ^= Stt[i + 12];
    }

    int ind = r;

    if (dec)
        ind = 31 - r;

    Stt[4] ^= RC4[ind];

    // AddConstant
    Stt[5] ^= RC3[ind];

    for (int i = 0; i < 16; i++)
        // AddTweakey
        Stt[i] ^= TK[ind % 4][i];

    if (r != 31) {
        int Temp[16];

        for (int i = 0; i < 16; i++)
            // Permutation
            Temp[P[i]] = Stt[i];

        for (int i = 0; i < 16; i++)
            // SBox
            Stt[i] = S[Temp[i]];
    }
}


void craft(int inputText[16], int outputText[16], int Key[2][16], int Tweak[16], bool dec) {

    // TweakKey
    int TK[4][16] = {{0}};

    // InterState
    int Stt[16] = {0};
// input to inter State
    for (int i = 0; i < 16; ++i) {
        Stt[i] = inputText[i];
    }

    // generate all TweakKey by Key and Tweak information
    craft_initialize_key(Key, Tweak, dec, TK);
// 32 craft_round Function
    for (int i = 0; i < 32; ++i) {
        craft_round(Stt, TK, i, dec);
    }
    // Inter State to Output
    for (int i = 0; i < 16; ++i) {
        outputText[i] = Stt[i];
    }
}


