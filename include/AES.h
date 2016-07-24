#ifndef AES_H
#define AES_H

#define RIJNDAEL	4

enum mode {
	ECB,
	CBC,
	OFB,
	CFB
};

enum operation {
	FIRST,
	STD,
	LAST
};

struct AES_context {
	enum mode mode;
	uint16_t key_size;
	uint8_t *key;
};
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
void
AES_expand_keys(uint8_t *key, uint16_t k);
void hex_dump(const char *def, uint8_t *data, uint16_t len,
		uint16_t br);

#endif
