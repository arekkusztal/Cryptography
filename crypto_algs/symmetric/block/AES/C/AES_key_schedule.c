#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <AES.h>
#include "AES.h"

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
