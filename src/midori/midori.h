//
// Created by 93462 on 2023/4/12.
//

#ifndef LIGHTWEIGHT_BLOCK_CIPHERS_MIDORI_H
#define LIGHTWEIGHT_BLOCK_CIPHERS_MIDORI_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

void midori_sp1(uint8_t *cell);

void midori_inv_sp1(uint8_t *cell);

void midori_sp2(uint8_t *cell);

void midori_inv_sp2(uint8_t *cell);

void midori_sp3(uint8_t *cell);

void midori_inv_sp3(uint8_t *cell);

void midori_sp4(uint8_t *cell);

void midori_inv_sp4(uint8_t *cell);

/**
 * midori 128 加密
 * @param plainText 明文
 * @param key 密钥
 * @param cipherText 密文
 */
void midori_encrypt(const uint8_t plainText[16], uint8_t key[16], uint8_t cipherText[16]);
/**
 * midori 128 解密
 * @param cipherText 密文
 * @param key 密钥
 * @param plainText 明文
 */
void midori_decrypt(const uint8_t cipherText[16], uint8_t key[16], uint8_t plainText[16]);

/**
 * S box
 * @param state 中间值
 */
void midori_sub_cell(uint8_t state[16]);

/**
 * 洗一下牌
 * @param state 中间值
 */
void midori_shuffle_cell(uint8_t state[16]);

/**
 * 反洗一下牌
 * @param state 中间值
 */
void midori_inv_shuffle_cell(uint8_t state[16]);

/**
 * 列混淆 MDS 矩阵
 * @param state 中间值
 */
void midori_mix_column(uint8_t state[16]);

/**
 * 生成轮密钥
 * @param key 原始密钥
 * @param round_keys 轮密钥
 */
void midori_key_generation(const uint8_t key[16], uint8_t round_keys[304]);


#ifdef __cplusplus
}
#endif


#endif //LIGHTWEIGHT_BLOCK_CIPHERS_MIDORI_H
