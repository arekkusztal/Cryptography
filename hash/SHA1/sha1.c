#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint32_t h0 = 0x67452301;
uint32_t h1 = 0xEFCDAB89;
uint32_t h2 = 0x98BADCFE;
uint32_t h3 = 0x10325476;
uint32_t h4 = 0xC3D2E1F0;

void rol(uint8_t *data, uint16_t bg);

uint8_t *SHA1(char *arg, int size)
{
	uint8_t *data;
	uint32_t a, b, c, d, e, f, k;
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



	for (i = 0; i < new_size; i+=64) {
		uint32_t *p = (uint32_t *)(data + i);
		for (j = 16; j < 79; j++) {
			data[j] = (data[j - 3] ^ data[j - 8] ^ data[j - 14] ^ data[j - 16]);
			rol(&data[j], 1);
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
			k = 0x5A827999;
		} else if (j > 19 && j <= 39) {
			f = b ^ c ^ d;
            k = 0x6ED9EBA1;
		} else if (j > 39 && j <= 59) {
			f = (b & c) | (b & d) | (c & d);
			k = 0x8F1BBCDC;
		} else {
			f = b & c & d;
			k = 0xCA62C1D6;
		}
	}

	free(data);
}
