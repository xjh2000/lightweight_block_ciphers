//
// Created by xjh on 2023/1/14.
//

#ifndef LIGHTWEIGHT_BLOCK_CIPHERS_DES_H
#define LIGHTWEIGHT_BLOCK_CIPHERS_DES_H

#include "stdint.h"

/**
 * @brief des 加密
 * @param plainText 明文 64 bit
 * @param key 密钥 64 bit
 * @param cipherText 密文 64 bit
 */
void des_encrypt(uint64_t plainText, uint64_t key, uint64_t cipherText);

/**
 * @brief 初始置换ip
 * @param plainText 明文
 * @param left 置换后的左半部
 * @param right 置换后的右半部
 */
void ip_permutation(uint8_t *plainText, uint8_t *left, uint8_t *right);

/**
 * @brief key pc1 置换
 * @param key 密钥
 * @param C
 * @param D
 */
void pc1_permutation(uint8_t *key, uint8_t *C, uint8_t *D);


/**
 * @brief key pc2 置换
 * @param C
 * @param D
 * @param key 密钥
 */
void pc2_permutation(uint8_t *C, uint8_t *D, uint8_t *key);

/**
 * @brief 密钥扩展
 * @param key 密钥
 * @param keys 扩展密钥
 */
void generate_keys(uint8_t *key, uint8_t **keys);


/**
 * @brief CD字节数组的左移
 * @param array CD字节数组
 * @param shift_size 左移大小 bit位单位
 */
void CD_shift(uint8_t *array,  uint8_t shift_size);

#endif //LIGHTWEIGHT_BLOCK_CIPHERS_DES_H
