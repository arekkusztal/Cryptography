#include <CRYPTO_LIB_block_modes.h>

void
CRYPTO_LIB_CBC_encrypt(struct CRYPTO_context *ctx)
{
	uint16_t i, block_nr;
	uint8_t * out = ctx->plaintext;
	uint16_t block_count = ctx->blocks_count;

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
	}
}

void
CRYPTO_LIB_CBC_decrypt(struct CRYPTO_context *ctx)
{
	uint16_t i, block_nr;
	uint8_t * out = ctx->plaintext;
	uint16_t block_count = ctx->blocks_count;

	for (block_nr = block_count - 1; block_nr > 0; block_nr --) {

		ctx->crypto_decrypt_block(out + ctx->block_size * block_nr, ctx);
		for (i =0; i < ctx->block_size; i++) {
			(out + ctx->block_size * block_nr)[i] ^=
					(out+ctx->block_size*(block_nr-1))[i];
		}
	}
	ctx->crypto_decrypt_block(out + ctx->block_size * block_nr, ctx);
	for (i = 0; i < ctx->block_size; i++) {
		(out + ctx->block_size * block_nr)[i] ^= ctx->iv[i];
	}
}
