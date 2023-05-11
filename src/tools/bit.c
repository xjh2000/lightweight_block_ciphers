//
// Created by 93462 on 2023/5/10.
//

#include "bit.h"

void bit_to_byte(const bool *bit, uint8_t *byte) {
    *byte = 0;
    for (int i = 0; i < 8; ++i) {
        if (bit[i]) {
            *byte += 1 << (7 - i);
        }
    }
}

void byte_to_bit(uint8_t byte, bool *bit) {
    for (int i = 0; i < 8; ++i) {
        bit[i] = false;
    }

    for (int i = 7; i >= 0; --i) {
        if (byte & 0x01) {
            bit[i] = true;
        }
        byte >>= 1;
    }
}
