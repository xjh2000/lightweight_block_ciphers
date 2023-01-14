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

// pc2
const static uint8_t key_pc2_table[48] = {
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32
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

void des_encrypt(uint8_t *plainText, uint8_t *key, uint8_t *cipherText) {

    uint8_t left[4] = {0};
    uint8_t right[4] = {0};
    uint8_t keys[][6] = {0};



//    ip_permutation(plainText, &left, &right);


}

void CD_shift(uint8_t *array, uint8_t shift_size) {
    unsigned char shift_byte, first_shift_bits, second_shift_bits, third_shift_bits, fourth_shift_bits;
    shift_byte = 0x80;
    for (int i = 1; i < shift_size; ++i) {
        shift_byte >>= 1;
        shift_byte |= 0x80;
    }

    first_shift_bits = shift_byte & array[0];
    second_shift_bits = shift_byte & array[1];
    third_shift_bits = shift_byte & array[2];
    fourth_shift_bits = shift_byte & array[3];

    array[0] <<= shift_size;
    array[0] |= (second_shift_bits >> (8 - shift_size));

    array[1] <<= shift_size;
    array[1] |= (third_shift_bits >> (8 - shift_size));

    array[2] <<= shift_size;
    array[2] |= (fourth_shift_bits >> (8 - shift_size));

    array[3] <<= shift_size;
    array[3] |= (first_shift_bits >> (4 - shift_size));

}

void pc2_permutation(uint8_t *C, uint8_t *D, uint8_t *key) {
    int shift_size;
    uint8_t shift_byte;
    for (int i = 0; i < 48; ++i) {
        shift_size = key_pc2_table[i];
        if (shift_size <= 28) {
            shift_byte = 0x80 >> ((shift_size - 1) % 8);
            shift_byte &= C[(shift_size - 1) / 8];
            shift_byte <<= ((shift_size - 1) % 8);
        } else {
            shift_byte = 0x80 >> ((shift_size - 29) % 8);
            shift_byte &= D[(shift_size - 29) / 8];
            shift_byte <<= ((shift_size - 29) % 8);
        }
        key[i / 8] |= (shift_byte >> i % 8);
    }
}

void generate_keys(uint8_t *key, uint8_t **keys) {
    uint8_t C[4] = {0};
    uint8_t D[4] = {0};
    int shift_size;

    pc1_permutation(key, C, D);

    for (int i = 0; i < 16; ++i) {
        shift_size = LS_table[i];
        CD_shift(C, shift_size);
        CD_shift(D, shift_size);
        pc2_permutation(C, D, &key[i]);

    }

}


