//
// Created by 93462 on 2023/5/10.
//

#ifndef LIGHTWEIGHT_BLOCK_CIPHERS_LLWBC_H
#define LIGHTWEIGHT_BLOCK_CIPHERS_LLWBC_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 密钥生成
 * @param key 密钥
 * @param kws 最前和最后使用的子密钥
 * @param krs 轮函数中使用的子密钥
 */
void llwbc_key_schedule(bool key[128], bool kws[2][64], bool krs[21][32]);

/**
 * 轮函数f
 * @param state8 中间状态
 */
void llwbc_f(bool state8[8]);

/**
 * p置换
 * @param state64 中间状态
 */
void llwbc_p(bool state64[64]);

/**
 * p逆置换
 * @param state64 中间状态
 */
void llwbc_p_inverse(bool state64[64]);

/**
 * llwbc-64/128
 * @param plain_text 明文
 * @param key 密钥
 * @param cipher_text 密文
 */
void llwbc_encrypt(const bool plain_text[64], bool key[128], bool cipher_text[64]);

#ifdef __cplusplus
}
#endif

#endif //LIGHTWEIGHT_BLOCK_CIPHERS_LLWBC_H
