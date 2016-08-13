#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

typedef struct Integer {
	uint8_t *data;
	uint16_t size;
} integer;

void hex_dump(const char *def, uint8_t *data, uint16_t len,
		uint16_t br)
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

#define HEX_ME(arg) (arg - (arg < 58 ? 48 : 55))

integer*
set_integer_b16(uint8_t *array) {
	int16_t i, k;
	uint16_t len;
	integer *R;
	uint8_t *temp;

	len = (strlen(array));
	len = len/2 + (len & 1);

	if (len & 1) {
		temp = malloc(len*2);
		temp[0] = '0';
		memcpy(&temp[1], array, len*2-1);
		array = temp;
	}

	printf("\nLen = %d", len);
	R = malloc(sizeof(integer));
	R->data = malloc(len);
	R->size = len;

	memset(R->data, 0, len);

	/* Optimize for 8B,4B archs and for SIMD later */
	for (i = len-1, k =0; i>=0; i--, k+=2) {
		R->data[i] += HEX_ME(array[k]) * 16;
		R->data[i] += HEX_ME(array[k + 1]);
	}

	if (len & 1)
		free(temp);

	hex_dump("Long number", R->data, 8 ,8);

	return R;
}


int main(int argc, char *argv[])
{
	integer *A;
	A = set_integer_b16("83F1B");

	return 0;
}
