#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <AES.h>
#include "AES_ECB_test_vectors.h"

#define KEY_SIZE	16

static
uint8_t expansion[14][32];
 
uint8_t key[16] = { 0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6d, 0x79, 0x20, 0x4b, 0x75,
		0x6e, 0x67, 0x20, 0x46, 0x75 };

uint8_t datablock[16] = { 0x54,0x77,0x6F,0x20,0x4F,0x6E,0x65,0x20,0x4E,0x69,0x6E,
		0x65,0x20,0x54,0x77,0x6F };

uint8_t datablock_2[32] = { 0x54,0x77,0x6F,0x20,0x4F,0x6E,0x65,0x20,0x4E,0x69,0x6E,
		0x65,0x20,0x54,0x77,0x6F, 0x54,0x77,0x6F,0x20,0x4F,0x6E,0x65,0x20,0x4E,0x69,0x6E,
		0x35,0x20,0x54,0x77,0x6F };

void hex_dump(const char *def, uint8_t *data, uint16_t len, uint16_t br)
{
	uint16_t i;
	
	printf("\n%s:\n", def);
	for (i = 0; i < len; ++i) {
		if (i && ( i % br ==0 ))
			printf("\n");
		printf("0x%02X ",data[i]);
	}
	printf("\n");
}


static inline
uint8_t get_S_BOX(uint16_t arg)
{
	printf("\n%d\n", arg);
	return 0;
}

void key_expand(uint8_t *out, uint8_t *in, uint16_t rcon)
{

	int i;

	uint8_t gw3[4], w4[4], w5[4], w6[4], w7[4];
	memcpy(gw3, &in[12], 4);
	rol(gw3,1);

	for (i =0; i< 4;i++) {
		gw3[i] = s_box[gw3[i]];

	}
	gw3[0] ^= rcon;

	for (i=0;i<4;i++) {
		w4[i] = gw3[i] ^ in[i];
	}
	for (i=0;i<4;i++) {
		w5[i] = w4[i] ^ in[i+4];
	}

	for (i=0;i<4;i++) {
		w6[i] = w5[i] ^ in[i+8];
	}

	for (i=0;i<4;i++) {
		w7[i] = w6[i] ^ in[i+12];
	}

	memcpy(out, w4, 4);
	memcpy(out+4, w5, 4);
	memcpy(out+8, w6, 4);
	memcpy(out+12, w7, 4);

}




void
AES_expand_keys(uint16_t k)
{
	int i;
	if (k == 128)
		k = 10;
	else if (k == 192)
		k = 12;
	else if (k == 256)
		k = 14;

	key_expand(expansion[0], key, 1);
	for (i = 1; i < k; i++)
		key_expand(expansion[i], expansion[i-1], rcon[i+1]);
}


void
AES_ECB_encrypt(uint8_t *out, struct AES_context *ctx, uint16_t block_nr)
{
	int i, block;
	AES_expand_keys(ctx->key_size);

	for (block = 0; block < block_nr; block ++) {

		AES_encrypt(out+16*block, key, expansion[0], FIRST);

		for (i = 1; i < 9; i++) {
			AES_encrypt(out+16*block, key, expansion[i], STD);
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
	ctx->mode = ECB;

	hex_dump("plaintext", datablock_2, 32, 16);

	AES_ECB_encrypt(datablock_2, ctx, sizeof(datablock_2)/16);

	hex_dump("ciphertext ", datablock_2, 32, 16);
	
	return 0;
}
