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

#ifdef __cplusplus
}
#endif

#endif //LIGHTWEIGHT_BLOCK_CIPHERS_AES_H
