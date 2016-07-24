#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <AES.h>
#include "AES_CTR_test_vectors.h"

void
AES_CTR_encrypt(uint8_t *out, struct AES_context *ctx, uint16_t block_nr)
{
	int i, block;
	uint64_t ctr = 0;
	uint8_t loc_iv[16];
	AES_expand_keys(ctx->key, ctx->key_size);

	for (block = 0; block < block_nr; block ++) {
		memcpy(loc_iv, iv, 16);

		uint64_t *p = (uint64_t *)&loc_iv[8];
		*p ^= ctr++;

		AES_encrypt(loc_iv, ctx->key, expansion[0], FIRST);

		for (i = 1; i < 9; i++) {
			AES_encrypt(loc_iv, NULL, expansion[i], STD);
		}

		AES_encrypt(loc_iv, NULL, expansion[9], LAST);

		for (i =0; i< 16; i++)
		{
			(out+16*block)[i] ^= loc_iv[i];
		}
	}
}

int main(int argc, char *argv[])
{
	int i;
	uint16_t key_size = 16;
	struct AES_context *ctx = malloc(sizeof(struct AES_context));

	ctx->key_size = 128;
	ctx->mode = CTR;
	ctx->key = skey;

	hex_dump("plaintext", datablock, sizeof(datablock), 16);

	AES_CTR_encrypt(datablock, ctx, sizeof(datablock)/16);

	hex_dump("ciphertext ", datablock, sizeof(datablock), 16);
	
	return 0;
}
