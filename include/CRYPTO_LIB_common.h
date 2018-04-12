#ifndef CRYPTO_LIB_COMMON_H
#define CRYPTO_LIB_COMMON_H

#include <stdint.h>
#include "Arus_dev_kit.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define foreach(arg, args) \
			decltype(&args[0]) arg; \
            arg = args;        \
            for (; arg < (decltype(arg))args + sizeof(args)/sizeof(*args); arg++ ) \

//for (; arg < (decltype(arg))args + sizeof(args)/sizeof(*args); arg++ ) \

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
	void (*crypto_decrypt_block)(uint8_t *plaintext,
			struct CRYPTO_context *ctx);
};

struct AES_test_vector
{
	enum mode mode;
	uint8_t iv[16];
	struct {
		uint8_t data[32];
		uint8_t len;
	} key;
	struct
	{
		uint8_t *data;
		uint16_t len;
	} plaintext;
	struct
	{
		uint8_t data[4096];
		uint16_t len;
	} ciphertext;
};

void ror_4(uint8_t *data, uint16_t bg);
void rol_4(uint8_t *data, uint16_t bg);

#ifdef __cplusplus
}
#endif

#endif
