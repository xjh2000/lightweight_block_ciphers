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
void llwbc_key_schedule(bool key[128], bool kws[2][64],bool krs[21][32]);

#ifdef __cplusplus
}
#endif

#endif //LIGHTWEIGHT_BLOCK_CIPHERS_LLWBC_H
