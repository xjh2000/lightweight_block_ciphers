//
// Created by xjh on 2023/7/28.
//

#ifndef LIGHTWEIGHT_BLOCK_CIPHERS_CRAFT_H
#define LIGHTWEIGHT_BLOCK_CIPHERS_CRAFT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

void craft_initialize_key(int Key[2][16], int Tweak[16], int dec, int TK[4][16]);

void craft_round(int Stt[16], int TK[4][16], int r, bool dec);

void craft(int inputText[16], int outputText[16], int Key[2][16], int Tweak[16], bool dec);

#ifdef __cplusplus
}
#endif

#endif //LIGHTWEIGHT_BLOCK_CIPHERS_CRAFT_H
