//
// Created by 93462 on 2023/4/12.
//

#include "midori.h"

static uint8_t sbox1[16] = {0x01, 0x00, 0x05, 0x03, 0x0e, 0x02, 0x0f, 0x07, 0x0d, 0x0a, 0x09, 0x0b, 0x0c, 0x08, 0x04,
                            0x06};

void midori_shuffle_cell(uint8_t *state) {
    uint8_t tempState[16] = {0};

    // (0,1,2,...,15) <- (0,10,5,15,14,4,11,1,9,3,12,6,7,13,2,8)
    tempState[0] = state[0];
    tempState[1] = state[10];
    tempState[2] = state[5];
    tempState[3] = state[15];
    tempState[4] = state[14];
    tempState[5] = state[4];
    tempState[6] = state[11];
    tempState[7] = state[1];
    tempState[8] = state[9];
    tempState[9] = state[3];
    tempState[10] = state[12];
    tempState[11] = state[6];
    tempState[12] = state[7];
    tempState[13] = state[13];
    tempState[14] = state[2];
    tempState[15] = state[8];

    for (int i = 0; i < 16; ++i) {
        state[i] = tempState[i];
    }

}

void midori_mix_column(uint8_t *state) {
    uint8_t tempState[16] = {0};

    // Almost MDS
    // [00 01 01 01]   [s0  s4  s8  s12]
    // [01 00 01 01] . [s1  s5  s9  s13]
    // [01 01 00 01]   [s2  s6  s10 s14]
    // [01 01 01 00]   [s3  s7  s11 s15]

    for (int i = 0; i < 4; ++i) {
        tempState[0 + i * 4] = state[1 + i * 4] ^ state[2 + i * 4] ^ state[3 + i * 4];
        tempState[1 + i * 4] = state[0 + i * 4] ^ state[2 + i * 4] ^ state[3 + i * 4];
        tempState[2 + i * 4] = state[0 + i * 4] ^ state[1 + i * 4] ^ state[3 + i * 4];
        tempState[3 + i * 4] = state[0 + i * 4] ^ state[1 + i * 4] ^ state[2 + i * 4];
    }

    for (int i = 0; i < 16; ++i) {
        state[i] = tempState[i];
    }

}

void midori_key_generation(const uint8_t *key, uint8_t *round_keys) {
    // TODO maybe some bug about the big and small EndOrder

    // roundConstant
    // 243f 6a88 85a3 08d3
    // 1319 8a2e 0370 7344
    // a409 3822 299f 31d0
    // 082e fa98 ec4e 6c89
    // 4528 21e6 38d0


    uint8_t roundConstant[19][16] = {
            {
                    0, 0, 1, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 1,
                    1, 1, 1, 1},
            {       0, 1, 1, 0,
                    1, 0, 1, 0,
                    1, 0, 0, 0,
                    1, 0, 0, 0},
            {       1, 0, 0, 0,
                    0, 1, 0, 1,
                    1, 0, 1, 0,
                    0, 0, 1, 1,},
            {       0, 0, 0, 0,
                    1, 0, 0, 0,
                    1, 1, 0, 1,
                    0, 0, 1, 1,},
            {       0, 0, 0, 1,
                    0, 0, 1, 1,
                    0, 0, 0, 1,
                    1, 0, 0, 1,},
            {       1, 0, 0, 0,
                    1, 0, 1, 0,
                    0, 0, 1, 0,
                    1, 1, 1, 0},
            {       0, 0, 0, 0,
                    0, 0, 1, 1,
                    0, 1, 1, 1,
                    0, 0, 0, 0},
            {       0, 1, 1, 1,
                    0, 0, 1, 1,
                    0, 1, 0, 0,
                    0, 1, 0, 0},
            {       1, 0, 1, 0,
                    0, 1, 0, 0,
                    0, 0, 0, 0,
                    1, 0, 0, 1},
            {       0, 0, 1, 1,
                    1, 0, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 1, 0,},
            {       0, 0, 1, 0,
                    1, 0, 0, 1,
                    1, 0, 0, 1,
                    1, 1, 1, 1,},
            {       0, 0, 1, 1,
                    0, 0, 0, 1,
                    1, 1, 0, 1,
                    0, 0, 0, 0},
            {       0, 0, 0, 0,
                    1, 0, 0, 0,
                    0, 0, 1, 0,
                    1, 1, 1, 0,},
            {       1, 1, 1, 1,
                    1, 0, 1, 0,
                    1, 0, 0, 1,
                    1, 0, 0, 0,},
            {       1, 1, 1, 0,
                    1, 1, 0, 0,
                    0, 1, 0, 0,
                    1, 1, 1, 0,},
            {       0, 1, 1, 0,
                    1, 1, 0, 0,
                    1, 0, 0, 0,
                    1, 0, 0, 1,},
            {       0, 1, 0, 0,
                    0, 1, 0, 1,
                    0, 0, 1, 0,
                    1, 0, 0, 0,},
            {       0, 0, 1, 0,
                    0, 0, 0, 1,
                    1, 1, 1, 0,
                    0, 1, 1, 0,},
            {       0, 0, 1, 1,
                    1, 0, 0, 0,
                    1, 1, 0, 1,
                    0, 0, 0, 0}
    };

    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                round_keys[i * 16 + j * 4 + k] = key[j * 4 + k] ^ roundConstant[i][k * 4 + j];
            }
        }
    }


}

void midori_sub_cell(uint8_t *state) {

    for (int i = 0; i < 4; ++i) {
        midori_sp1(&state[0 + i * 4]);
        state[0 + i * 4] = sbox1[state[0 + i * 4] >> 4] << 4 | sbox1[(uint8_t) (state[0 + i * 4] << 4) >> 4];
        midori_inv_sp1(&state[0 + i * 4]);

        midori_sp2(&state[1 + i * 4]);
        state[1 + i * 4] = sbox1[state[1 + i * 4] >> 4] << 4 | sbox1[(uint8_t) (state[1 + i * 4] << 4) >> 4];
        midori_inv_sp2(&state[1 + i * 4]);

        midori_sp3(&state[2 + i * 4]);
        state[2 + i * 4] = sbox1[state[2 + i * 4] >> 4] << 4 | sbox1[(uint8_t) (state[2 + i * 4] << 4) >> 4];
        midori_inv_sp3(&state[2 + i * 4]);

        midori_sp4(&state[3 + i * 4]);
        state[3 + i * 4] = sbox1[state[3 + i * 4] >> 4] << 4 | sbox1[(uint8_t) (state[3 + i * 4] << 4) >> 4];
        midori_inv_sp4(&state[3 + i * 4]);

    }
}

void midori_sp1(uint8_t *cell) {
    uint8_t tempCell = {0};
    // 4,1,6,3,0,5,2,7
    tempCell |= (*cell & (0x80 >> 4)) << (4 - 0);
    tempCell |= (*cell & (0x80 >> 1)) << (1 - 1);
    tempCell |= (*cell & (0x80 >> 6)) << (6 - 2);
    tempCell |= (*cell & (0x80 >> 3)) << (3 - 3);
    tempCell |= (*cell & (0x80 >> 0)) >> (4 - 0);
    tempCell |= (*cell & (0x80 >> 5)) >> (5 - 5);
    tempCell |= (*cell & (0x80 >> 2)) >> (6 - 2);
    tempCell |= (*cell & (0x80 >> 7)) >> (7 - 7);

    *cell = tempCell;
}

void midori_inv_sp1(uint8_t *cell) {
    midori_sp1(cell);
}

void midori_sp2(uint8_t *cell) {
    uint8_t tempCell = {0};
    // 1,6,7,0,5,2,3,4
    tempCell |= (*cell & (0x80 >> 1)) << (1 - 0);
    tempCell |= (*cell & (0x80 >> 6)) << (6 - 1);
    tempCell |= (*cell & (0x80 >> 7)) << (7 - 2);
    tempCell |= (*cell & (0x80 >> 0)) >> (3 - 0);
    tempCell |= (*cell & (0x80 >> 5)) << (5 - 4);
    tempCell |= (*cell & (0x80 >> 2)) >> (5 - 2);
    tempCell |= (*cell & (0x80 >> 3)) >> (6 - 3);
    tempCell |= (*cell & (0x80 >> 4)) >> (7 - 4);

    *cell = tempCell;
}

void midori_inv_sp2(uint8_t *cell) {
    uint8_t tempCell = {0};
    // 3,0,5,6,7,4,1,2
    tempCell |= (*cell & (0x80 >> 3)) << (3 - 0);
    tempCell |= (*cell & (0x80 >> 0)) >> (1 - 0);
    tempCell |= (*cell & (0x80 >> 5)) << (5 - 2);
    tempCell |= (*cell & (0x80 >> 6)) << (6 - 3);
    tempCell |= (*cell & (0x80 >> 7)) << (7 - 4);
    tempCell |= (*cell & (0x80 >> 4)) >> (5 - 4);
    tempCell |= (*cell & (0x80 >> 1)) >> (6 - 1);
    tempCell |= (*cell & (0x80 >> 2)) >> (7 - 2);

    *cell = tempCell;
}

void midori_sp3(uint8_t *cell) {
    uint8_t tempCell = {0};
    // 2,3,4,1,6,7,0,5
    tempCell |= (*cell & (0x80 >> 2)) << (2 - 0);
    tempCell |= (*cell & (0x80 >> 3)) << (3 - 1);
    tempCell |= (*cell & (0x80 >> 4)) << (4 - 2);
    tempCell |= (*cell & (0x80 >> 1)) >> (3 - 1);
    tempCell |= (*cell & (0x80 >> 6)) << (6 - 4);
    tempCell |= (*cell & (0x80 >> 7)) << (7 - 5);
    tempCell |= (*cell & (0x80 >> 0)) >> (6 - 0);
    tempCell |= (*cell & (0x80 >> 5)) >> (7 - 5);

    *cell = tempCell;
}

void midori_inv_sp3(uint8_t *cell) {
    uint8_t tempCell = {0};
    // 6,3,0,1,2,7,4,5
    tempCell |= (*cell & (0x80 >> 6)) << (6 - 0);
    tempCell |= (*cell & (0x80 >> 3)) << (3 - 1);
    tempCell |= (*cell & (0x80 >> 0)) >> (2 - 0);
    tempCell |= (*cell & (0x80 >> 1)) >> (3 - 1);
    tempCell |= (*cell & (0x80 >> 2)) >> (4 - 2);
    tempCell |= (*cell & (0x80 >> 7)) << (7 - 5);
    tempCell |= (*cell & (0x80 >> 4)) >> (6 - 4);
    tempCell |= (*cell & (0x80 >> 5)) >> (7 - 5);

    *cell = tempCell;
}

void midori_sp4(uint8_t *cell) {

    uint8_t tempCell = {0};
    // 7,4,1,2,3,0,5,6
    tempCell |= (*cell & (0x80 >> 7)) << (7 - 0);
    tempCell |= (*cell & (0x80 >> 4)) << (4 - 1);
    tempCell |= (*cell & (0x80 >> 1)) >> (2 - 1);
    tempCell |= (*cell & (0x80 >> 2)) >> (3 - 2);
    tempCell |= (*cell & (0x80 >> 3)) >> (4 - 3);
    tempCell |= (*cell & (0x80 >> 0)) >> (5 - 0);
    tempCell |= (*cell & (0x80 >> 5)) >> (6 - 5);
    tempCell |= (*cell & (0x80 >> 6)) >> (7 - 6);

    *cell = tempCell;
}

void midori_inv_sp4(uint8_t *cell) {

    uint8_t tempCell = {0};
    // 5,2,3,4,1,6,7,0
    tempCell |= (*cell & (0x80 >> 5)) << (5 - 0);
    tempCell |= (*cell & (0x80 >> 2)) << (2 - 1);
    tempCell |= (*cell & (0x80 >> 3)) << (3 - 2);
    tempCell |= (*cell & (0x80 >> 4)) << (4 - 3);
    tempCell |= (*cell & (0x80 >> 1)) >> (4 - 1);
    tempCell |= (*cell & (0x80 >> 6)) << (6 - 5);
    tempCell |= (*cell & (0x80 >> 7)) << (7 - 6);
    tempCell |= (*cell & (0x80 >> 0)) >> (7 - 0);

    *cell = tempCell;
}

void midori_inv_shuffle_cell(uint8_t *state) {
    uint8_t tempState[16] = {0};

    // (0,1,2,...,15) <- (0,7,14,9,5,2,11,12,15,8,1,6,10,13,4,3)
    tempState[0] = state[0];
    tempState[1] = state[7];
    tempState[2] = state[14];
    tempState[3] = state[9];
    tempState[4] = state[5];
    tempState[5] = state[2];
    tempState[6] = state[11];
    tempState[7] = state[12];
    tempState[8] = state[15];
    tempState[9] = state[8];
    tempState[10] = state[1];
    tempState[11] = state[6];
    tempState[12] = state[10];
    tempState[13] = state[13];
    tempState[14] = state[4];
    tempState[15] = state[3];

    for (int i = 0; i < 16; ++i) {
        state[i] = tempState[i];
    }
}

void midori_encrypt(const uint8_t *plainText, uint8_t *key, uint8_t *cipherText) {
    uint8_t round_keys[304] = {0};
    uint8_t state[16] = {0};
    midori_key_generation(key, round_keys);

    for (int i = 0; i < 16; ++i) {
        state[i] = plainText[i] ^ key[i];
    }

    for (int i = 0; i < 19; ++i) {
        midori_sub_cell(state);
        midori_shuffle_cell(state);
        midori_mix_column(state);
        for (int j = 0; j < 16; ++j) {
            state[j] = state[j] ^ round_keys[j + i * 16];
        }
    }

    midori_sub_cell(state);

    for (int i = 0; i < 16; ++i) {
        cipherText[i] = state[i] ^ key[i];
    }
}

void midori_decrypt(const uint8_t *cipherText, uint8_t *key, uint8_t *plainText) {
    uint8_t round_keys[304] = {0};
    uint8_t state[16] = {0};
    midori_key_generation(key, round_keys);

    for (int i = 0; i < 16; ++i) {
        state[i] = cipherText[i] ^ key[i];
    }

    for (int i = 18; i >= 0; --i) {
        midori_sub_cell(state);
        midori_mix_column(state);
        midori_inv_shuffle_cell(state);

        midori_mix_column(&round_keys[i * 16]);
        midori_inv_shuffle_cell(&round_keys[i * 16]);
        for (int j = 0; j < 16; ++j) {
            state[j] = state[j] ^ round_keys[j + i * 16];
        }
    }

    midori_sub_cell(state);

    for (int i = 0; i < 16; ++i) {
        plainText[i] = state[i] ^ key[i];
    }
}
