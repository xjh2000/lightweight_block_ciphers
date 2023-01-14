//
// Created by xjh on 2023/1/14.
//

#include "des.h"

// ip permutation table
// let plainText to left part and right part
const static uint8_t ip_table[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
};

// pc1
const static uint8_t key_pc1_table[56] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
};

// 每轮移动的位数
const static uint8_t LS_table[16] = {
        1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};


void ip_permutation(uint8_t *plainText, uint8_t *left, uint8_t *right) {
    uint8_t ip_permute[8] = {0};
    uint8_t shift_byte = 0;
    for (int i = 0; i < 64; ++i) {
        shift_byte = 0x80 >> ((ip_table[i] - 1) % 8);
        shift_byte &= plainText[(ip_table[i] - 1) / 8];
        shift_byte <<= (ip_table[i] - 1) % 8;
        ip_permute[i / 8] |= shift_byte >> (i % 8);
    }
    for (int i = 0; i < 4; ++i) {
        left[i] = ip_permute[i];
        right[i] = ip_permute[i + 4];
    }
}

void pc1_permutation(uint8_t *key, uint8_t *C, uint8_t *D) {
    uint8_t temp[7] = {0};
    uint8_t shift_byte;
    for (int i = 0; i < 56; ++i) {
        shift_byte = 0x80 >> ((key_pc1_table[i] - 1) % 8);
        shift_byte &= key[(key_pc1_table[i] - 1) / 8];
        shift_byte <<= (key_pc1_table[i] - 1) % 8;

        temp[i / 8] |= shift_byte >> (i % 8);
    }

    for (int i = 0; i < 3; ++i) {
        C[i] = temp[i];
    }
    C[3] = temp[3] & 0xf0;

    for (int i = 0; i < 3; ++i) {
        D[i] = (temp[i + 3] & 0x0f) << 4;
        D[i] |= (temp[i + 4] & 0xf0) >> 4;
    }

    D[3] = (temp[6] & 0x0f) << 4;

}

void des_encrypt(uint64_t plainText, uint64_t key, uint64_t cipherText) {

    uint32_t left = 0;
    uint32_t right = 0;
    uint64_t keys[16] = {0};

    generate_keys(key, keys);

//    ip_permutation(plainText, &left, &right);


}

void generate_keys(uint64_t key, uint64_t *keys) {
    uint32_t C = 0;
    uint32_t D = 0;

//    pc1_permutation(key, &C, &D);

    for (int i = 0; i < 16; ++i) {
        C = (C << LS_table[i] | C >> (28 - LS_table[i])) & 0xfffffff;
        D = (D << LS_table[i] | D >> (28 - LS_table[i])) & 0xfffffff;
        keys[i] = ((uint64_t) C) << 28 | D;
    }
}


