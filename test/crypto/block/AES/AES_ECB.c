#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <AES.h>
#include "AES_ECB_test_vectors.h"
 
void
AES_ECB_encrypt(uint8_t *out, struct AES_context *ctx, uint16_t block_nr)
{
	int i, block;
	AES_expand_keys(ctx);

	for (block = 0; block < block_nr; block ++) {

		AES_encrypt(out+16*block, ctx->key, ctx->expansion[0], FIRST);

		for (i = 1; i < 9; i++) {
			AES_encrypt(out+16*block, NULL, ctx->expansion[i], STD);
		}

		AES_encrypt(out+16*block, NULL, ctx->expansion[9], LAST);
	}
}



int main(int argc, char *argv[])
{
	int i;
	uint16_t key_size = 16;
	struct AES_context *ctx = malloc(sizeof(struct AES_context));

//	ctx->key_size = 128;
	ctx->mode = ECB;
	ctx->key = skey;

	hex_dump("plaintext", datablock_2, 32, 16);

	AES_ECB_encrypt(datablock_2, ctx, sizeof(datablock_2)/16);

	hex_dump("ciphertext ", datablock_2, 32, 16);
	
	return 0;
}
