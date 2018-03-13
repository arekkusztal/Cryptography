#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Arus_dev_kit.h>

#define BE
#ifdef BE
uint32_t h0 = 0x67452301;
uint32_t h1 = 0xEFCDAB89;
uint32_t h2 = 0x98BADCFE;
uint32_t h3 = 0x10325476;
uint32_t h4 = 0xC3D2E1F0;

uint32_t k0 = 0x5A827999;
uint32_t k1 = 0x6ED9EBA1;
uint32_t k2 = 0x8F1BBCDC;
uint32_t k3 = 0xCA62C1D6;

#else
uint32_t h0 = 0x01234567;
uint32_t h1 = 0x89ABCDEF;
uint32_t h2 = 0xFEDCBA98;
uint32_t h3 = 0x76543210;
uint32_t h4 = 0xF0E1D2C3;

uint32_t k0 = 0x9979825A;
uint32_t k1 = 0xA1EBD96E;
uint32_t k2 = 0xDCBC1B8F;
uint32_t k3 = 0xD6C162CA;

#endif

uint32_t lrotate32(uint32_t data, uint8_t shift)
{
	int i;
	uint32_t temp = data >> (32 - shift);
	data = ( data << shift) | temp;
	return data;
}

#define lrotate32(word,bits) \
                (((word) << (bits)) | ((word) >> (32-(bits))))

//static uint8_t string[] = "jkijkljklmklmnlmnomnopnopq";
/*
static uint8_t string[] = {
		0x6A, 0x6B, 0x69, 0x6A, 0x6B, 0x6C, 0x6A, 0x6B, 0x6C, 0x6D, 0x6B, 0x6C, 0x6D, 0x6E, 0x6C, 0x6D,
		0x6E, 0x6F, 0x6D, 0x6E, 0x6F, 0x70, 0x6E, 0x6F, 0x70, 0x71, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A,
};
*/
/*
static uint8_t string[] = {
		0x6A, 0x6B, 0x69, 0x6A, 0x6B, 0x6C, 0x6A, 0x6B, 0x6C, 0x6D, 0x6B, 0x6C, 0x6D, 0x6E, 0x6C, 0x6D,
		0x6E, 0x6F, 0x6D, 0x6E, 0x6F, 0x70, 0x6E, 0x6F, 0x70, 0x71, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A,
};
*/

static uint8_t string[] = {
		0x64, 0x63, 0x62, 0x61, 0x00, 0x00, 0x80, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
};

uint8_t *SHA1(uint8_t *ret, uint8_t *arg, int size)
{
	size = 64;
	uint32_t t;
	uint32_t w[80] = { };
	uint32_t A, B, C, D, E;
	uint32_t TEMP;
	uint32_t R[5] = { };

	memcpy(w, string, 64);

	printf("\nsize of string = %lu", sizeof(string));
	hex_dump("w", (uint8_t *)w, 320, 16);

	for (t = 16; t < 80; t++) {
		w[t] = lrotate32( (w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16]), 1);
	}

	A = h0, B = h1, C = h2, D = h3, E = h4;
	for (t = 0; t < 80; t++) {
		if (t >= 0 && t <= 19) {
			TEMP = lrotate32(A, 5) + ((B & C) | ((~B) & D)) + E + w[t] + k0;
		} else if (t >= 20 && t <= 39) {
			TEMP = lrotate32(A, 5) + (B ^ C ^ D) + E + w[t] + k1;
		} else if (t >= 40 && t <= 59) {
			TEMP = lrotate32(A, 5) + ((B & C) | (B & D) | (C & D)) + E + w[t] + k2;
		} else if (t >= 60 && t <= 79) {
			TEMP = lrotate32(A, 5) + (B ^ C ^ D) + E + w[t] + k3;
		}

		E = D;
		D = C;
		C = lrotate32(B, 30);
		B = A;
		A = TEMP;
	}

	h0 = h0 + A;
	h1 = h1 + B;
	h2 = h2 + C;
	h3 = h3 + D;
	h4 = h4 + E;

	R[0] = h0;
	R[1] = h1;
	R[2] = h2;
	R[3] = h3;
	R[4] = h4;

	hex_dump("Res", (uint8_t *)R, 20, 20);

}

uint8_t *SHA1_2(uint8_t *ret, char *arg, int size)
{
	uint32_t *data;
	uint32_t a, b, c, d, e, f, k, temp, h[5] = { }, r[5] = { };
	int new_size, i, j, l, padding;
	printf("\n size = %d\n", size);
	if (size % 64 < 56) {
		padding = 64 - (size % 64);
		printf("\nPadding = %d", padding);
	} else {
		padding = 128 - (size % 64);
		printf("\nPadding 1 = %d", padding);
	}
	new_size = size + padding + 64 * 4;
	data = malloc(new_size);

	memset(data, 0, new_size);
	printf("\n new_size = %d", new_size);
	data[16] = 0x80;



	for (i = 0; i < new_size; i+=64) {
		uint32_t *p = (uint32_t *)(data + i);
		for (j = 16; j < 80; j++) {
			data[j] = (data[j - 3] ^ data[j - 8] ^ data[j - 14] ^ data[j - 16]);
			data[j] = lrotate32(data[j], 1);
			//hex_dump("1", (uint8_t *)data, 320, 16);

		}
	}

	a = h0;
	b = h1;
	c = h2;
	d = h3;
	e = h4;

	for (j = 0; j < 79; j++) {
		if (j >= 0 && j <= 19) {
			f = (b & c) | (~b & d);
#ifdef BE
			k = 0x5A827999;
#else
			k = 0x9979825A;
#endif
		} else if (j > 19 && j <= 39) {
			f = b ^ c ^ d;
#ifdef BE
            k = 0x6ED9EBA1;
#else
            k = 0xA1EBD96E;
#endif
		} else if (j > 39 && j <= 59) {
			f = (b & c) | (b & d) | (c & d);
#ifdef BE
			k = 0x8F1BBCDC;
#else
			k = 0xDCBC1B8F;
#endif
		} else {
			f = b ^ c ^ d;
#ifdef BE
			k = 0xCA62C1D6;
#else
			k = 0xD6C162CA;
#endif
		}


		temp = lrotate32(a, 5) + f + e + k + data[j];
		e = d;
		d = lrotate32(c,30);
		b = a;
		a = temp;

	}

	h[0] = h[0] + a;
	h[1] = h[1] + b;
	h[2] = h[2] + c;
	h[3] = h[3] + d;
	h[4] = h[4] + e;


	r[0] = h[4];
	r[1] = h[3];
	r[2] = h[2];
	r[3] = h[1];
	r[4] = h[0];

	memcpy(ret, r, 20);


	free(data);
	return ret;
}
