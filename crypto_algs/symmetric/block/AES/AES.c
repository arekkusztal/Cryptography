#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <AES.h>
#include "AES.h"

#define AES_DEBUG
#define KEY_EXPAND_2

void rol(uint8_t *data, uint16_t bg)
{
	int i;

	uint8_t temp[4];
	for (i = bg; i < bg + 4; i++) {
		temp[i - bg] = data[i & 3];
	}
	memcpy(data, temp, 4);
}

void ror(uint8_t *data, uint16_t bg)
{
	int i;

	uint8_t temp[4];
	for (i = bg; i < bg + 4; i++) {
		temp[i - bg] = data[(4 - 2*bg + i) & 3];
	}
	memcpy(data, temp, 4);
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

void mix_columns(uint8_t *state)
{
	int i;
	uint8_t temp[16];

	memcpy(temp, state, 16);

    for (i = 0; i < 4; i+=1) {
    	state[i] = GMUL2[temp[i]] ^ GMUL3[temp[i+4]] ^ temp[i+8] ^ temp[i+12];
    	state[i+4] = temp[i] ^ GMUL2[temp[i + 4]] ^ GMUL3[temp[i+8]] ^ temp[i+12];
    	state[i+8] = temp[i] ^ temp[i + 4] ^ GMUL2[temp[i+8]] ^ GMUL3[temp[i+12]];
    	state[i+12] = GMUL3[temp[i]] ^ temp[i + 4] ^ temp[i+8] ^ GMUL2[temp[i+12]];
    }
}

void reverse_mix_columns(uint8_t *state)
{
	int i;
	uint8_t temp[16];

	memcpy(temp, state, 16);

    for (i = 0; i < 4; i+=1) {
    	state[i] = GMUL14[temp[i]] ^ GMUL11[temp[i+4]] ^ GMUL13[temp[i+8]] ^ GMUL9[temp[i+12]];
    	state[i+4] = GMUL9[temp[i]] ^ GMUL14[temp[i + 4]] ^ GMUL11[temp[i+8]] ^ GMUL13[temp[i+12]];
    	state[i+8] = GMUL13[temp[i]] ^ GMUL9[temp[i + 4]] ^ GMUL14[temp[i+8]] ^ GMUL11[temp[i+12]];
    	state[i+12] = GMUL11[temp[i]] ^ GMUL13[temp[i + 4]] ^ GMUL9[temp[i+8]] ^ GMUL14[temp[i+12]];
    }
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

void key_expansion(struct AES_context *ctx)
{
	int i = ctx->key_size, key_size = ctx->key_size, j, r = 1;
	uint8_t *in = ctx->expansion;
	uint8_t gw3[4];

	while (i < (ctx->key_rounds + 1) * AES_BLOCK_SZ) {

		if (i % key_size == 0) {
			memcpy(gw3, &in[i - 4], 4);

			rol(gw3,1);

			for (j = 0; j < 4; j++) {
				gw3[j] = s_box[gw3[j]];

			}
			gw3[0] ^= rcon[r++];

			for (j = 0; j < 4; j++)
				ctx->expansion[i+j] = gw3[j] ^ in[i - key_size + j];
			i+=4;

		}
		else {
			if (ctx->key_size == 32 && i % 32 == 16) {
				for (j = 0; j < 4; j++)
					ctx->expansion[i+j] = s_box[ctx->expansion[i - 4 + j]] ^ in[i - key_size + j];

			} else {
				for (j = 0; j < 4; j++)
					ctx->expansion[i+j] = ctx->expansion[i - 4 + j] ^ in[i - key_size + j];
			}
			i+=4;
		}



	}

}

void key_expand(struct AES_context *ctx, uint8_t *out, uint8_t *in, uint16_t rcon)
{
	int i, j;

	uint8_t gw3[4];
	uint8_t w[32];
	memcpy(gw3, &in[ctx->key_size - 4], 4);

	rol(gw3,1);

	for (i = 0; i < 4; i++) {
		gw3[i] = s_box[gw3[i]];

	}
	gw3[0] ^= rcon;

	for (i = 0; i < 4; i++) {
		w[i] = gw3[i] ^ in[i];
	}
	i = 4;

	while (i < ctx->key_size) {
		if (ctx->key_size == 32 && i % 32 == 16) {
			for (j = 0; j < 4; j++)
				w[i + j] = s_box[w[i - 4 + j]] ^ in[i + j];
			i+=4;
		}
		else {
			for (j =0; j < 4; j++)
				w[i + j] = w[i - 4 + j] ^ in[i + j];
			i+=4;
		}
	}

	memcpy(out, w, ctx->key_size);
}

int AES_get_rcon_numer(enum AES_KEY_ROUNDS key_rounds)
{
	switch (key_rounds){
	case AES_KEY_ROUND_10:
		return 10;
	case AES_KEY_ROUND_12:
		return 8;
	case AES_KEY_ROUND_14:
		return 7;
	}
}

void *
AES_expand_keys(struct AES_context *ctx)
{
	int i;

	memcpy(ctx->expansion, ctx->key, ctx->key_size);
#ifdef KEY_EXPAND_1
	for (i = 1; i <= AES_get_rcon_numer(ctx->key_rounds); i++)
		key_expand(ctx, &ctx->expansion[ctx->key_size*i],
				&ctx->expansion[ctx->key_size*(i-1)], rcon[i]);
#else
	key_expansion(ctx);
#endif

	return ctx->expansion;
}

void AES_decrypt(uint8_t *out, uint8_t *in, uint8_t *key_2,
				enum operation op)
{

	int i;
	uint8_t state[16], key_inv[16], key_inv_2[16];

	matrix_inverse(key_inv_2, key_2);
	matrix_inverse(state, out);

	for (i = 0 ;i < 16; i++) {
		state[i] = state[i] ^ key_inv_2[i];
	}

	if (op != LAST)
		reverse_mix_columns(state);

	for (i = 1; i < RIJNDAEL; i++) {
		ror(&state[RIJNDAEL*i], i);
	}

	for (i = 0; i<16; i++) {
		state[i] = s_box_inv[state[i]];
	}

	if (op == FIRST) {
		matrix_inverse(key_inv, in);
		for (i = 0; i < 16; i++) {
			state[i] ^= key_inv[i];
		}
	}

	matrix_inverse(out, state);
}


void AES_encrypt(uint8_t *out, uint8_t *in, uint8_t *key_2,
				enum operation op)
{
	int i;
	uint8_t state[16], key_inv[16], key_inv_2[16];

	matrix_inverse(state, out);
	matrix_inverse(key_inv_2, key_2);

	if (op == FIRST) {
		matrix_inverse(key_inv, in);
		for (i = 0; i < 16; i++) {
			state[i] ^= key_inv[i];
		}

	}

	for (i = 0; i<16; i++) {
		state[i] = s_box[state[i]];
	}

	for (i = 1; i < RIJNDAEL; i++) {
		rol(&state[RIJNDAEL*i], i);
	}

	if (op != LAST) {
		mix_columns(state);
	}

	for (i = 0 ;i < 16; i++) {
		state[i] = state[i] ^ key_inv_2[i];
	}

	matrix_inverse(out, state);
}

void AES_decrypt_block(uint8_t *plaintext, struct CRYPTO_context *ctx)
{
	int i;
	AES_decrypt(plaintext, NULL, &ctx->expansion[AES_BLOCK_SZ * ctx->key_rounds], LAST);
	for (i = ctx->key_rounds - 1; i >= 2; i--) {
		AES_decrypt(plaintext, NULL, &ctx->expansion[AES_BLOCK_SZ * i], STD);
	}
	AES_decrypt(plaintext, ctx->key, ctx->expansion + AES_BLOCK_SZ, FIRST);
}

void AES_encrypt_block(uint8_t *plaintext, struct CRYPTO_context *ctx)
{
	int i;

	AES_encrypt(plaintext, ctx->key, ctx->expansion + AES_BLOCK_SZ, FIRST);

	for (i = 2; i <= ctx->key_rounds - 1; i++) {
		AES_encrypt(plaintext, NULL, &ctx->expansion[AES_BLOCK_SZ * i], STD);
	}

	AES_encrypt(plaintext, NULL, &ctx->expansion[AES_BLOCK_SZ * ctx->key_rounds], LAST);


}
