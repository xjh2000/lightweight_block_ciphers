//
// Created by xjh on 2023/1/14.
//

#ifndef LIGHTWEIGHT_BLOCK_CIPHERS_DES_H
#define LIGHTWEIGHT_BLOCK_CIPHERS_DES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

/**
 * @brief des 加密
 * @param plainText 明文 64 bit
 * @param key 密钥 64 bit
 * @param cipherText 密文 64 bit
 */
void des_encrypt(uint8_t *plainText, uint8_t *key, uint8_t *cipherText);

/**
 * @brief des 加密
 * @param cipherText 密文 64 bit
 * @param key 密钥 64 bit
 * @param plainText 明文 64 bit
 */
void des_decrypt(uint8_t *cipherText, uint8_t *key, uint8_t *plainText);

/**
 * @brief 初始置换ip
 * @param plainText 明文
 * @param left 置换后的左半部
 * @param right 置换后的右半部
 */
void des_ip_permutation(uint8_t *plainText, uint8_t *left, uint8_t *right);

/**
 * @brief key pc1 置换
 * @param key 密钥
 * @param C
 * @param D
 */
void des_pc1_permutation(uint8_t *key, uint8_t *C, uint8_t *D);


/**
 * @brief key pc2 置换
 * @param C
 * @param D
 * @param key 密钥
 */
void des_pc2_permutation(uint8_t *C, uint8_t *D, uint8_t key[6]);

/**
 * @brief 密钥扩展
 * @param key 密钥
 * @param keys 扩展密钥
 */
void des_generate_keys(uint8_t *key, uint8_t keys[16][6]);


/**
 * @brief CD字节数组的左移
 * @param array CD字节数组
 * @param shift_size 左移大小 bit位单位
 */
void des_CD_shift(uint8_t *array, uint8_t shift_size);
/**
 * @brief des 轮函数
 * @param left
 * @param right
 * @param key 密钥
 */
void des_turn(uint8_t left[4], uint8_t right[4], uint8_t key[6]);

/**
 * @brief S盒代换
 * @param extend E扩展后的数据
 * @param S S盒
 */
void des_s_box_change(uint8_t extend[6], uint8_t S[4]);

#ifdef __cplusplus
}
#endif

#endif //LIGHTWEIGHT_BLOCK_CIPHERS_DES_H
