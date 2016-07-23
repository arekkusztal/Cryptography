#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <AES.h>
#include "AES_CBC_test_vectors.h"

void
AES_CBC_encrypt(uint8_t *out, struct AES_context *ctx, uint16_t block_nr)
{
	int i, block;
	AES_expand_keys(ctx->key, ctx->key_size);

	for (block = 0; block < block_nr; block ++) {

		if (block == 0) {
			for (i =0; i < 16; i++) {
				(out+16*block)[i] ^= iv[i];
			}
		}
		else {
			for (i =0; i < 16; i++) {
				(out+16*(block))[i] ^= (out+16*(block-1))[i];
			}
		}

		AES_encrypt(out+16*block, ctx->key, expansion[0], FIRST);

		for (i = 1; i < 9; i++) {
			AES_encrypt(out+16*block, NULL, expansion[i], STD);
		}

		AES_encrypt(out+16*block, NULL, expansion[9], LAST);
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

	hex_dump("plaintext", datablock_2, 32, 16);

	AES_CBC_encrypt(datablock_2, ctx, sizeof(datablock_2)/16);

	hex_dump("ciphertext ", datablock_2, 32, 16);
	
	return 0;
}
