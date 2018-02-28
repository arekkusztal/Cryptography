#ifndef AES_H
#define AES_H

#define RIJNDAEL		4
#define AES_BLOCK_SZ	16

enum mode {
	ECB,
	CBC,
	OFB,
	CFB,
	CTR,
	GCM
};

enum operation {
	FIRST,
	STD,
	LAST
};

enum AES_KEY_SZ {
	AES_KEY_SZ_16 = 16,
	AES_KEY_SZ_24 = 24,
	AES_KEY_SZ_32 = 32
};

enum AES_KEY_ROUNDS {
	AES_KEY_ROUND_10 = 10,
	AES_KEY_ROUND_12 = 12,
	AES_KEY_ROUND_14 = 14,
};

struct CRYPTO_context {
	enum mode mode;
	enum AES_KEY_SZ key_size;
	enum AES_KEY_ROUNDS key_rounds;
	uint8_t expansion[14][32];
	uint8_t *key;
	uint8_t iv[16];
};

struct AES_context {
	enum mode mode;
	enum AES_KEY_SZ key_size;
	enum AES_KEY_ROUNDS key_rounds;
	uint8_t expansion[14][32];
	uint8_t *key;
	uint8_t iv[16];
};

/* Make it memory not contigous, clear after or other change */
extern uint8_t expansion[14][32];

extern uint8_t s_box[256];
extern uint8_t rcon[256];

void rol(uint8_t *data, uint16_t bg);
void rijandel_mix(uint8_t *r);
void rijndeal_mix_help(uint8_t *state, uint16_t off);
static inline void
matrix_inverse(uint8_t *out, uint8_t *in);
void AES_encrypt(uint8_t *out, uint8_t *in, uint8_t *key_2,
				enum operation op);
void key_expand(uint8_t *out, uint8_t *in, uint16_t rcon);
void *
AES_expand_keys(struct AES_context *ctx);
void hex_dump(const char *def, uint8_t *data, uint16_t len,
		uint16_t br);

#endif
