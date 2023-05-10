//
// Created by 93462 on 2023/5/10.
//

#ifndef LIGHTWEIGHT_BLOCK_CIPHERS_BIT_H
#define LIGHTWEIGHT_BLOCK_CIPHERS_BIT_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 8 bit to 1 byte
 * @param bit 0 index is MSB
 * @param byte 1 byte
 */
void bit_to_byte(const bool bit[8], uint8_t *byte);

/**
 * 1 byte to 8 bit
 * @param byte 1 byte
 * @param bit 0 index is MSB
 */
void byte_to_bit(uint8_t byte, bool bit[8]);

#ifdef __cplusplus
}
#endif
#endif //LIGHTWEIGHT_BLOCK_CIPHERS_BIT_H
