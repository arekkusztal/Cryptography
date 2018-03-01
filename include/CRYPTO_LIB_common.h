#ifndef CRYPTO_LIB_COMMON_H
#define CRYPTO_LIB_COMMON_H

#include <stdint.h>

enum AES_KEY_SZ {
	AES_KEY_SZ_16 = 16,
	AES_KEY_SZ_24 = 24,
	AES_KEY_SZ_32 = 32
};

enum AES_KEY_ROUNDS {
	AES_KEY_ROUND_10 = 10,
	AES_KEY_ROUND_12 = 12,
	AES_KEY_ROUND_14 = 14,
};

enum mode {
	ECB,
	CBC,
	OFB,
	CFB,
	CTR,
	GCM
};

struct CRYPTO_context {
	enum mode mode;
	enum AES_KEY_SZ key_size;
	enum AES_KEY_ROUNDS key_rounds;
	uint8_t expansion[256];
	uint8_t *key;
	uint8_t *iv;
	uint8_t *plaintext;
	uint16_t blocks_count;
	uint16_t block_size;
	void (*crypto_encrypt_block)(uint8_t *plaintext,
			struct CRYPTO_context *ctx);
};


#endif
