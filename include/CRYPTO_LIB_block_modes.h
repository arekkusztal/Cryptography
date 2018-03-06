#ifndef CRYPTO_LIB_BLOCK_MODES_H
#define CRYPTO_LIB_BLOCK_MODES_H

#include <stdint.h>
#include "CRYPTO_LIB_common.h"
#include "Arus_dev_kit.h"

void
CRYPTO_LIB_CBC_encrypt(struct CRYPTO_context *ctx);

void
CRYPTO_LIB_CBC_decrypt(struct CRYPTO_context *ctx);

void
CRYPTO_LIB_CTR_encrypt(struct CRYPTO_context *ctx);

#endif
