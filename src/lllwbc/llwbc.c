//
// Created by 93462 on 2023/5/10.
//

#include <stdint.h>
#include "llwbc.h"
#include "../tools/bit.h"

uint8_t cks[21][4] = {
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

void llwbc_key_schedule(bool *key, bool (*kws)[64], bool (*krs)[32]) {
    // K = kw || ke

    // kw1 = kw
    for (int i = 0; i < 64; ++i) {
        kws[0][i] = key[i];
    }
    // kw2 = (kw >>> 1) ^ (kw >> 63)
    kws[1][0] = key[63];
    for (int i = 1; i < 63; ++i) {
        kws[1][i] = key[i - 1];
    }
    kws[1][63] = key[62] ^ key[0];

    // ke = K_1 || K_2
    // r = 1,3,...21 k^{r-1} = K_1 ^ ck^{r}
    // r = 2,4,...20 k^{r-1} = K_2 ^ ck^{r}
    bool temp[8] = {0};
    for (int i = 0; i < 10; ++i) {
        // 1,3,...19
        // r = i * 2
        for (int j = 0; j < 4; ++j) {
            // index = j * 8 + k
            byte_to_bit(cks[i * 2][j], temp);
            for (int k = 0; k < 8; ++k) {
                krs[i * 2][j * 8 + k] = key[64 + j * 8 + k] ^ temp[k];
            }
        }

        // 2,3,....20
        // r = i * 2 + 1
        for (int j = 0; j < 4; ++j) {
            // index = j * 8 + k
            byte_to_bit(cks[i * 2 + 1][j], temp);
            for (int k = 0; k < 8; ++k) {
                krs[i * 2 + 1][j * 8 + k] = key[96 + j * 8 + k] ^ temp[k];
            }
        }
    }

    // r = 21
    for (int j = 0; j < 4; ++j) {
        // index = j * 8 + k
        byte_to_bit(cks[20][j], temp);
        for (int k = 0; k < 8; ++k) {
            krs[20][j * 8 + k] = key[64 + j * 8 + k] ^ temp[k];
        }
    }
}
