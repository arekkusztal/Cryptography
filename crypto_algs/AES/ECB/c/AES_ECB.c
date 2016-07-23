#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define KEY_SIZE	16

 uint8_t s_box[256] = 
 {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
 };
 
uint8_t key[16] = { 0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6d, 0x79, 0x20, 0x4b, 0x75,
		0x6e, 0x67, 0x20, 0x46, 0x75 };
		
uint8_t expanded_1[16];
uint8_t expanded_2[16];
uint8_t expanded_3[16];
uint8_t expanded_4[16];
uint8_t expanded_5[16];
uint8_t expanded_6[16];
uint8_t expanded_7[16];
uint8_t expanded_8[16];
uint8_t expanded_9[16];
uint8_t expanded_10[16];
		
uint8_t datablock[16] = { 0x54,0x77,0x6F,0x20,0x4F,0x6E,0x65,0x20,0x4E,0x69,0x6E,
		0x65,0x20,0x54,0x77,0x6F };

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
void AES_encrypt(uint8_t *out, uint8_t *in, uint8_t *key_2)
{
	int i;
	uint8_t state[16], key_inv[16], key_inv_2[16];
	
	for (i = 0;i<4;i++) {
		state[4*i] = out[i];
		state[4*i + 1] = out[i+4];
		state[4*i + 2] = out[i+8];
		state[4*i + 3] = out[i+12];
	}
	for (i = 0;i<4;i++) {
		key_inv[4*i] = in[i];
		key_inv[4*i + 1] = in[i+4];
		key_inv[4*i + 2] = in[i+8];
		key_inv[4*i + 3] = in[i+12];
	}
	
	for (i = 0;i<4;i++) {
		key_inv_2[4*i] = key_2[i];
		key_inv_2[4*i + 1] = key_2[i+4];
		key_inv_2[4*i + 2] = key_2[i+8];
		key_inv_2[4*i + 3] = key_2[i+12];
	}
	for (i=0;i<KEY_SIZE; i++) {
		state[i] ^= key_inv[i];
		state[i] = s_box[state[i]];
	}
	for (i =1; i<4; i++) {
		rol(&state[4*i], i);
	}
	//hex_dump("State 1", state, KEY_SIZE, 4);
	
	rijndeal_mix_help(state, 0);
	rijndeal_mix_help(state, 1);
	rijndeal_mix_help(state, 2);
	rijndeal_mix_help(state, 3);
	
	for (i =0 ;i <16; i++) {
		out[i] = state[i] ^ key_inv_2[i];
	}
	hex_dump("State 1", state, KEY_SIZE, 4);
	hex_dump("Inverted key 1", key_inv, KEY_SIZE, 4);
	hex_dump("First round encryption", out, KEY_SIZE, 4);
}

int main(int argc, char *argv[])
{
	int i;

	key_expand(expanded_1, key, 1);
	hex_dump("Expanded key 1", expanded_1, KEY_SIZE, 16);
	
	key_expand(expanded_2, expanded_1, 2);
	hex_dump("Expanded key 2", expanded_2, KEY_SIZE, 16);
	
	key_expand(expanded_3, expanded_2, 4);
	hex_dump("Expanded key 3", expanded_3, KEY_SIZE, 16);
	
	key_expand(expanded_4, expanded_3, 8);
	hex_dump("Expanded key 4", expanded_4, KEY_SIZE, 16);
	
	key_expand(expanded_5, expanded_4, 0x10);
	hex_dump("Expanded key 5", expanded_5, KEY_SIZE, 16);
	
	key_expand(expanded_6, expanded_5, 0x20);
	hex_dump("Expanded key 6", expanded_6, KEY_SIZE, 16);

	key_expand(expanded_7, expanded_6, 0x40);
	hex_dump("Expanded key 7", expanded_7, KEY_SIZE, 16);
	
	key_expand(expanded_8, expanded_7, 0x80);
	hex_dump("Expanded key 8", expanded_8, KEY_SIZE, 16);
	
	key_expand(expanded_9, expanded_8, 0x1B);
	hex_dump("Expanded key 9", expanded_9, KEY_SIZE, 16);
	
	key_expand(expanded_10, expanded_9, 0x36);
	hex_dump("Expanded key 10", expanded_10, KEY_SIZE, 16);
	
	AES_encrypt(datablock, key, expanded_1);
	
	
//	uint8_t r[4] = { 0xEB, 0x93, 0xC7, 0x20 };
//	gmix_column(r);
	
	
	return 0;
}