//
// Created by 93462 on 2023/3/8.
//

#ifndef LIGHTWEIGHT_BLOCK_CIPHERS_AES_H
#define LIGHTWEIGHT_BLOCK_CIPHERS_AES_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 通过原始密钥 扩展出额外11轮密钥  1轮初始化 10轮轮函数
 * @param key 原始密钥
 * @param keys 扩展密钥
 */
void aes_key_expand(uint8_t key[16], uint8_t keys[176]);

/**
 * 行移位变换 循环左移
 * @param state 变换文本
 */
void aes_shift_row(uint8_t state[16]);

/**
 * 逆行移位变换 循环右移
 * @param state 变换文本
 */
void aes_inv_shift_row(uint8_t state[16]);

/**
 * 列混淆变化
 * @param state 原文本
 * @param nextState 变化后文本
 */
void aes_mix_columns(uint8_t state[16], uint8_t nextState[16]);

/**
 * 逆列混淆变化
 * @param state 原文本
 * @param nextState 变化后文本
 */
void aes_inv_mix_columns(uint8_t state[16], uint8_t nextState[16]);

/**
 * aes 128 加密
 * @param plainText 明文
 * @param key 密钥
 * @param cipherText 密文
 */
void aes_encrypt(uint8_t plainText[16], uint8_t key[16], uint8_t cipherText[16]);
/**
 * aes 128 加密优化版
 * @param plainText 明文
 * @param key 密钥
 * @param cipherText 密文
 */
void aes_encrypt_plus(uint8_t plainText[16], uint8_t key[16], uint8_t cipherText[16]);

/**
 * 生成优化后加密轮中所需T表
 */
void aes_generate_t_tables();

/**
 * aes 128 解密
 * @param cipherText 密文
 * @param key 密钥
 * @param plainText 明文
 */
void aes_decrypt(uint8_t cipherText[16], uint8_t key[16], uint8_t plainText[16]);

#ifdef __cplusplus
}
#endif

#endif; //LIGHTWEIGHT_BLOCK_CIPHERS_AES_H
