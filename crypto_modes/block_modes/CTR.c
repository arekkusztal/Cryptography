#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <AES.h>

void
CRYPTO_LIB_CTR_encrypt(struct CRYPTO_context *ctx)
{
	uint16_t i, j, block_nr;
	uint8_t * out = ctx->plaintext;
	uint16_t block_count = ctx->blocks_count;
	uint8_t iv[16];

	memcpy(iv, ctx->iv, 16);


	printf("\n TUUU ");
	for (i = 0; i < block_count; i++) {
		ctx->crypto_encrypt_block(iv, ctx);
		for (j = 0; j < ctx->block_size; j++)
			(out + ctx->block_size * block_nr)[j] ^= iv[j];
	}

/*
	block_nr = 0;
	for (i = 0; i < ctx->block_size; i++) {
		(out + ctx->block_size * block_nr)[i] ^= ctx->iv[i];
	}

	ctx->crypto_encrypt_block(out + ctx->block_size * block_nr, ctx);

	for (block_nr = 1; block_nr < block_count; block_nr ++) {

		for (i =0; i < ctx->block_size; i++) {
			(out + ctx->block_size * block_nr)[i] ^=
					(out+ctx->block_size*(block_nr-1))[i];
		}

		ctx->crypto_encrypt_block(out + ctx->block_size * block_nr, ctx);
	} */
}
