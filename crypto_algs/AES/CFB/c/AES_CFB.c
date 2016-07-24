#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <AES.h>
#include "AES_CFB_test_vectors.h"

void
AES_CFB_encrypt(uint8_t *out, struct AES_context *ctx, uint16_t block_nr)
{
	int i, block;
	uint8_t *IV = iv;
	AES_expand_keys(ctx->key, ctx->key_size);

	for (block = 0; block < block_nr; block ++) {

		if (block != 0) {
			IV = &(out+16*block-1)[i];
		}

		AES_encrypt(IV, ctx->key, expansion[0], FIRST);

		for (i = 1; i < 9; i++) {
			AES_encrypt(IV, NULL, expansion[i], STD);
		}

		AES_encrypt(IV, NULL, expansion[9], LAST);

		for (i =0; i< 16; i++)
		{
			(out+16*block)[i] ^= IV[i];
		}
	}
}

int main(int argc, char *argv[])
{
	int i;
	uint16_t key_size = 16;
	struct AES_context *ctx = malloc(sizeof(struct AES_context));

	ctx->key_size = 128;
	ctx->mode = CFB;
	ctx->key = skey;

	hex_dump("plaintext", datablock, sizeof(datablock), 16);

	AES_CFB_encrypt(datablock, ctx, sizeof(datablock)/16);

	hex_dump("ciphertext ", datablock, sizeof(datablock), 16);
	
	return 0;
}
