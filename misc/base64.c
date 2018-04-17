#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <Arus_dev_kit.h>

static const char B[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz0123456789+/";

uint8_t *strtbase64(uint8_t *msg, uint32_t sz)
{
	int i, k;

	uint8_t *out, *mess;
	uint32_t tlen, diff;

	diff = sz % 3;
	sz = 4*sz/3;
	tlen = (sz & ~3) + 4*(!!(sz & 3));

	mess = malloc(tlen);
	memset(mess, 0, tlen);

	for (i = 0; i< sz; i++) {
		mess[tlen - i-1] = msg[i];
	}

	out = malloc(sz + sz/3);

	i = 0;
	for (k = 0; k < tlen; k++) {
		if (!(k & 3) && k)
			i++;
		uint32_t dword = *(uint32_t *)&mess[ (tlen - 4) -3 * i];
		dword <<= (k & 3) * 6;
		dword >>= 26;
		out[k] = B[dword];
	}

	if (diff == 1) {
		out[tlen-1] = '=';
		out[tlen-2] = '=';
	}
	else if (diff == 2)
		out[tlen-1] = '=';

	free(mess);

	return out;
}

char *base64_to_str(uint8_t *msg, uint32_t sz)
{
	uint32_t i, k, j, l;
	uint32_t __sz = sz * 3 / 4;
	if (msg[sz - 1] == '=')
		__sz--;
	if (msg[sz - 2] == '=')
		__sz--;

	l = 0;
	j = __sz;
	char *str = malloc(sz);
	char *out_str = malloc(__sz);
	for (k = 0; k < sz; k++) {
		if (k && !(k & 3))
			l++;
		for (i = 0; i < sizeof(B); i++) {
			if (B[i] == msg[k]) {
				*(uint32_t *)&str[sz - 4 - (3 * l)] |= i << (26 - 6 * (k & 3));
			}
		}
	}

	for (i = 0; i < __sz; i++) {
		out_str[i] = str[sz - i - 1];
	}

	free(str);
	return out_str;
}
