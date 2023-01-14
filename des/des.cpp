//
// Created by xjh on 2023/1/14.
//

#include "des.h"
#include "stdio.h"

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


void ip_permutation(uint64_t plainText, uint32_t *left, uint32_t *right) {
    uint64_t ip_permute = 0;
    for (int i = 0; i < 64; ++i) {
        if (((uint64_t) 1 << (ip_table[i] - 1)) & (plainText)) {
            ip_permute |= (uint64_t) 1 << i;
        }
    }
    *left = (uint32_t) (ip_permute >> 32);
    *right = (uint32_t) (ip_permute << 32 >> 32);
}

void pc1_permutation(uint64_t key, uint32_t *C, uint32_t *D) {
    uint64_t temp = 0;
    for (int i = 0; i < 56; ++i) {
        if (((uint64_t) 1 << (key_pc1_table[i] - 1)) & (key)) {
            temp |= (uint64_t) 1 << i;
        }
    }
    *C = (uint32_t) (temp >> 28);
    *D = (uint32_t) (temp << 36 >> 36);
}

void des_encrypt(uint64_t plainText, uint64_t key, uint64_t cipherText) {

    uint32_t left = 0;
    uint32_t right = 0;
    uint64_t keys[16] = {0};

    generate_keys(key, keys);

    ip_permutation(plainText, &left, &right);


}

void generate_keys(uint64_t key, uint64_t *keys) {
    uint32_t C = 0;
    uint32_t D = 0;

    pc1_permutation(key, &C, &D);

    for (int i = 0; i < 16; ++i) {
        C = (C << LS_table[i] | C >> (28 - LS_table[i])) & 0xfffffff;
        D = (D << LS_table[i] | D >> (28 - LS_table[i])) & 0xfffffff;
        keys[i] = ((uint64_t) C) << 28 | D;
    }
}


