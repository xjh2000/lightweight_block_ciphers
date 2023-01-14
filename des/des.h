//
// Created by xjh on 2023/1/14.
//

#ifndef LIGHTWEIGHT_BLOCK_CIPHERS_DES_H
#define LIGHTWEIGHT_BLOCK_CIPHERS_DES_H

#include "stdint.h"

/**
 *  des 加密
 * @param plainText 明文 64 bit
 * @param key 密钥 64 bit
 * @param cipherText 密文 64 bit
 */
void des_encrypt(uint64_t plainText,uint64_t key,uint64_t cipherText);

/**
 *  初始置换ip
 * @param plainText 明文
 * @param left 置换后的左半部
 * @param right 置换后的右半部
 */
void ip_permutation( uint64_t plainText, uint32_t *left, uint32_t *right);

void generate_keys(uint64_t key, uint64_t *keys);

/**
 *  key pc1 置换
 * @param key 密钥
 * @param C
 * @param D
 */
void pc1_permutation(uint64_t key, uint32_t *C, uint32_t *D);
#endif //LIGHTWEIGHT_BLOCK_CIPHERS_DES_H
