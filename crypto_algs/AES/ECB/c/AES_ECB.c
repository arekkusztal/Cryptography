#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <AES.h>
#include "AES_ECB_test_vectors.h"

#define KEY_SIZE	16

#define RIJNDAEL	4

enum operation {
	FIRST,
	STD,
	LAST
};

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

void rol(uint8_t *data, uint16_t bg)
{
	int i;
		
	uint8_t temp[4];
	for (i=bg;i<bg+4; i++) {
		temp[i-bg] = data[i & 3];
	}
	memcpy(data, temp, 4);
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

void rijandel_mix(uint8_t *r) {
        uint8_t a[4];
        uint8_t b[4];
        uint8_t c;
        uint8_t h;
        for(c=0;c<4;c++) {
                a[c] = r[c];
                h = (uint8_t)((int8_t)r[c] >> 7);
                b[c] = r[c] << 1;
                b[c] ^= 0x1B & h;
        }
	
        r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
        r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
        r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
        r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
}
void rijndeal_mix_help(uint8_t *state, uint16_t off)
{
	int i;
	uint8_t column[4];
	for (i =0;i<4;i++) {
		column[i] = state[i*4+off];
	}	
	rijandel_mix(column);
	for (i =0;i<4;i++) {
		state[i*4+off] = column[i];
	}	
}

static inline void
matrix_inverse(uint8_t *out, uint8_t *in)
{
	int i;
	for (i = 0;i<4;i++) {
		out[4*i] = in[i];
		out[4*i + 1] = in[i+4];
		out[4*i + 2] = in[i+8];
		out[4*i + 3] = in[i+12];
	}
}
void ECB_encrypt(uint8_t *out, uint8_t *in, uint8_t *key_2,
				enum operation op)
{
	int i;
	uint8_t state[16], key_inv[16], key_inv_2[16];
	
	matrix_inverse(state, out);
	matrix_inverse(key_inv_2, key_2);
	
	if (op == FIRST) {
		matrix_inverse(key_inv, in);
		for (i=0;i<KEY_SIZE; i++) {
			state[i] ^= key_inv[i];
		}
	}

	for (i=0;i<KEY_SIZE; i++) {
		state[i] = s_box[state[i]];
	}

	for (i =1; i< RIJNDAEL; i++) {
		rol(&state[RIJNDAEL*i], i);
	}
	
	if (op != LAST) {
		for (i = 0; i< RIJNDAEL; i++)
			rijndeal_mix_help(state, i);
	}
	
	for (i =0 ;i <16; i++) {
		state[i] = state[i] ^ key_inv_2[i];
	}

	matrix_inverse(out, state);
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

struct AES_context {
	enum mode mode;
	uint16_t key_size;
};

void
AES_encrypt(uint8_t *out, struct AES_context *ctx, uint16_t block_nr)
{
	int i, block;
	AES_expand_keys(ctx->key_size);

	for (block = 0; block < block_nr; block ++) {

		ECB_encrypt(out+16*block, key, expansion[0], FIRST);

		for (i = 1; i < 9; i++) {
			ECB_encrypt(out+16*block, key, expansion[i], STD);
		}

		ECB_encrypt(out+16*block, NULL, expansion[9], LAST);
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

	AES_encrypt(datablock_2, ctx, sizeof(datablock_2)/16);

	hex_dump("ciphertext ", datablock_2, 32, 16);
	
	return 0;
}
