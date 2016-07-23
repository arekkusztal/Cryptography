#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <AES.h>
#include "AES_OFB_test_vectors.h"

void
AES_OFB_encrypt(uint8_t *out, struct AES_context *ctx, uint16_t block_nr)
{
	int i, block;
	AES_expand_keys(ctx->key, ctx->key_size);

	for (block = 0; block < block_nr; block ++) {

		hex_dump("iv ", iv, sizeof(datablock), 16);
		AES_encrypt(iv, ctx->key, expansion[0], FIRST);

		for (i = 1; i < 9; i++) {
			AES_encrypt(iv, NULL, expansion[i], STD);
		}

		AES_encrypt(iv, NULL, expansion[9], LAST);

		hex_dump("iv ", iv, sizeof(datablock), 16);
		for (i =0; i< 16; i++)
		{
			out[i] ^= iv[i];
		}
	}
}

int main(int argc, char *argv[])
{
	int i;
	uint16_t key_size = 16;
	struct AES_context *ctx = malloc(sizeof(struct AES_context));

	ctx->key_size = 128;
	ctx->mode = CBC;
	ctx->key = skey;

	hex_dump("plaintext", datablock, sizeof(datablock), 16);

	AES_OFB_encrypt(datablock, ctx, sizeof(datablock)/16);

	hex_dump("ciphertext ", datablock, sizeof(datablock), 16);
	
	return 0;
}
