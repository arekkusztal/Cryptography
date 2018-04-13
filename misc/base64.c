#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

static const char B[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz0123456789+/";

uint8_t *strtbase64(uint8_t *msg, uint32_t sz)
{
	int i, k;

	printf("\n msg size = %u", sz);
	uint8_t *out, *mess;
	uint32_t tlen, diff;

	diff = sz % 3;
	sz = 4*sz/3;
	tlen = (sz & ~3) + 4*(!!(sz & 3));

	printf("\n sz = %u \n diff = %u",sz,diff);
	mess = malloc(tlen);
	memset(mess, 0, tlen);

	for (i = 0; i< sz; i++) {
		mess[tlen - i-1] = msg[i];
	}

	out = malloc(sz + sz/3);

	i = 0;
	for (k =0; k < tlen; k++) {
		if (!(k & 3) && k)
			i++;
		uint32_t dword = *(uint32_t *)&mess[ (tlen - 4) -3 * i];
		dword <<= (k & 3) * 6;
		dword >>= 26;
		printf("\n Dword = %u B[] = %c", dword, B[dword]);
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
/*
int main()
{
	uint8_t *msg;

	msg = strtbase64(message, sizeof(message)-1);

	printf("\nout:\n%s\n", msg);
	return 0;
}
*/
