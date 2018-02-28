#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <AES.h>
#include "AES_CBC_test_vectors.h"

enum AES_KEY_ROUNDS AES_get_key_rounds(enum AES_KEY_SZ AES_key_size)
{
	switch (AES_key_size)
	{
		case AES_KEY_SZ_16:
			return AES_KEY_ROUND_10;
		case AES_KEY_SZ_24:
			return AES_KEY_ROUND_12;
		case AES_KEY_SZ_32:
			return AES_KEY_ROUND_14;
	}
}

void AES_encrypt_block(uint8_t *plaintext, struct AES_context *ctx)
{
	int i;
	AES_encrypt(plaintext, ctx->key, ctx->expansion[0], FIRST);

	for (i = 1; i < ctx->key_rounds - 1; i++) {
		AES_encrypt(plaintext, NULL, ctx->expansion[i], STD);
	}

	AES_encrypt(plaintext, NULL, ctx->expansion[ctx->key_rounds - 1], LAST);
}

void
CRYPTO_LIB_CBC_encrypt(uint8_t *out, struct AES_context *ctx, uint16_t block_count)
{
	int i, block_nr;

	block_nr = 0;
	for (i = 0; i < AES_BLOCK_SZ; i++) {
		(out + AES_BLOCK_SZ * block_nr)[i] ^= iv[i];
	}

	AES_encrypt_block(out + AES_BLOCK_SZ * block_nr, ctx);

	for (block_nr = 1; block_nr < block_count; block_nr ++) {

		for (i =0; i < AES_BLOCK_SZ; i++) {
			(out + AES_BLOCK_SZ * block_nr)[i] ^= (out+AES_BLOCK_SZ*(block_nr-1))[i];
		}

		AES_encrypt_block(out + AES_BLOCK_SZ * block_nr, ctx);
	}
}

void AES_CBC_encrypt_test(uint8_t *out, struct AES_context *ctx, uint16_t block_count)
{
	AES_expand_keys(ctx);

	CRYPTO_LIB_CBC_encrypt(out, ctx, block_count);
}

int main(int argc, char *argv[])
{
	int i;
	/* Create context */
	struct AES_context *ctx = malloc(sizeof(struct AES_context));

	memset(ctx, 0, sizeof(*ctx));
	ctx->key_size = AES_KEY_SZ_16;
	ctx->key_rounds =  AES_get_key_rounds(ctx->key_size);
	ctx->mode = CBC;
	ctx->key = skey;

	hex_dump("plaintext", datablock_2, 32, 16);

	AES_CBC_encrypt_test(datablock_2, ctx, sizeof(datablock_2)/16);

	hex_dump("ciphertext ", datablock_2, 32, 16);
	
	return 0;
}

