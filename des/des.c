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
//末置换
const static uint8_t ipr_table[64] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
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

//扩展置换，将数据从32位扩展为48位
static const uint8_t extend_32to48[48] = {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1
};
uint8_t S1[] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};
uint8_t S2[] = {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};
uint8_t S3[] = {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12};
uint8_t S4[] = {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};
uint8_t S5[] = {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3};
uint8_t S6[] = {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};
uint8_t S7[] = {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};
uint8_t S8[] = {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

// P盒置换
const static uint8_t p_table[32] = {
        16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
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
    uint8_t shift_size = 0;
    uint8_t shift_byte = 0;
    uint8_t ipr_permutation[8] = {0};
    uint8_t keys[16][6] = {0};
    uint8_t temp;

    ip_permutation(plainText, left, right);
    generate_keys(key, keys);

    for (int i = 0; i < 15; ++i) {
        des_turn(left, right, keys[i]);

        // left and right swap
        for (int j = 0; j < 4; ++j) {
            temp = left[j];
            left[j] = right[j];
            right[j] = temp;
        }
    }
    // don't swap left and right
    des_turn(left, right, keys[15]);

    for (int i = 0; i < 4; ++i) {
        ipr_permutation[i] = left[i];
        ipr_permutation[i + 4] = right[i];
    }

    // ipr permutation
    for (int i = 0; i < 64; ++i) {
        shift_size = ipr_table[i];
        shift_byte = 0x80 >> ((shift_size - 1) % 8);
        shift_byte &= ipr_permutation[(shift_size - 1) / 8];
        shift_byte <<= ((shift_size - 1) % 8);

        cipherText[i / 8] |= (shift_byte >> i % 8);
    }

}

void des_turn(uint8_t left[4], uint8_t right[4], uint8_t key[6]) {
    uint8_t right_extend[6] = {0};
    uint8_t S[4] = {0};
    uint8_t shift_size = 0;
    uint8_t shift_byte = 0;
    // extend right 32 bit to 48 bit
    for (int i = 0; i < 48; ++i) {
        shift_size = extend_32to48[i];
        shift_byte = 0x80 >> ((shift_size - 1) % 8);
        shift_byte &= right[(shift_size - 1) / 8];
        shift_byte <<= ((shift_size - 1) % 8);

        right_extend[i / 8] |= shift_byte >> (i % 8);
    }
    // right extend xor key
    for (int i = 0; i < 6; ++i) {
        right_extend[i] ^= key[i];
    }
    // S box change
    s_box_change(right_extend, S);

    // clean right_extend for p permutation result
    for (int i = 0; i < 4; ++i) {
        right_extend[i] = 0;
    }

    // p permutation
    for (int i = 0; i < 32; ++i) {
        shift_size = p_table[i];
        shift_byte = 0x80 >> ((shift_size - 1) % 8);
        shift_byte &= S[(shift_size - 1) / 8];
        shift_byte <<= ((shift_size - 1) % 8);

        right_extend[i / 8] |= shift_byte >> (i % 8);
    }

    // left xor p permutation result
    for (int i = 0; i < 4; ++i) {
        left[i] ^= right_extend[i];
    }

}

void s_box_change(uint8_t extend[6], uint8_t S[4]) {
    uint8_t row, column;

    for (int i = 0; i < 4; ++i) {
        S[i] = 0;
    }

    // Byte 1
    row = 0;
    row |= ((extend[0] & 0x80) >> 6);
    row |= ((extend[0] & 0x04) >> 2);

    column = 0;
    column |= ((extend[0] & 0x78) >> 3);

    S[0] |= ((uint8_t) S1[row * 16 + column] << 4);

    row = 0;
    row |= (extend[0] & 0x02);
    row |= ((extend[1] & 0x10) >> 4);

    column = 0;
    column |= ((extend[0] & 0x01) << 3);
    column |= ((extend[1] & 0xE0) >> 5);

    S[0] |= (uint8_t) S2[row * 16 + column];

    // Byte 2
    row = 0;
    row |= ((extend[1] & 0x08) >> 2);
    row |= ((extend[2] & 0x40) >> 6);

    column = 0;
    column |= ((extend[1] & 0x07) << 1);
    column |= ((extend[2] & 0x80) >> 7);

    S[1] |= ((uint8_t) S3[row * 16 + column] << 4);

    row = 0;
    row |= ((extend[2] & 0x20) >> 4);
    row |= (extend[2] & 0x01);

    column = 0;
    column |= ((extend[2] & 0x1E) >> 1);

    S[1] |= (uint8_t) S4[row * 16 + column];

    // Byte 3
    row = 0;
    row |= ((extend[3] & 0x80) >> 6);
    row |= ((extend[3] & 0x04) >> 2);

    column = 0;
    column |= ((extend[3] & 0x78) >> 3);

    S[2] |= ((uint8_t) S5[row * 16 + column] << 4);

    row = 0;
    row |= (extend[3] & 0x02);
    row |= ((extend[4] & 0x10) >> 4);

    column = 0;
    column |= ((extend[3] & 0x01) << 3);
    column |= ((extend[4] & 0xE0) >> 5);

    S[2] |= (uint8_t) S6[row * 16 + column];

    // Byte 4
    row = 0;
    row |= ((extend[4] & 0x08) >> 2);
    row |= ((extend[5] & 0x40) >> 6);

    column = 0;
    column |= ((extend[4] & 0x07) << 1);
    column |= ((extend[5] & 0x80) >> 7);

    S[3] |= ((uint8_t) S7[row * 16 + column] << 4);

    row = 0;
    row |= ((extend[5] & 0x20) >> 4);
    row |= (extend[5] & 0x01);

    column = 0;
    column |= ((extend[5] & 0x1E) >> 1);

    S[3] |= (uint8_t) S8[row * 16 + column];

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

void pc2_permutation(uint8_t *C, uint8_t *D, uint8_t key[6]) {
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
        key[i / 8] |= (shift_byte >> (i % 8));
    }
}

void generate_keys(uint8_t *key, uint8_t keys[16][6]) {
    uint8_t C[4] = {0};
    uint8_t D[4] = {0};
    int shift_size;

    pc1_permutation(key, C, D);

    for (int i = 0; i < 16; ++i) {
        shift_size = LS_table[i];
        CD_shift(C, shift_size);
        CD_shift(D, shift_size);
        pc2_permutation(C, D, keys[i]);

    }

}


