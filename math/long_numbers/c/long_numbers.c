#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <long_numbers.hpp>
/** TODO
 * This functions need much optimization
 */

integer*
set_integer(uint8_t *array) {
	int16_t i, k;
	uint16_t len;
	uint16_t odd = 0;
	integer *R;
	uint8_t *temp;

	len = (strlen((const char *)array));
	odd = (len & 1);
	len = len/2 + odd;

	if (odd) {
		temp = malloc(len*2);
		temp[0] = '0';
		memcpy(&temp[1], array, len*2-1);
		array = temp;
	}

	R = malloc(sizeof(integer));
	R->data = malloc(len);
	R->size = len;

	memset(R->data, 0, len);

	/* Optimize for 8B,4B archs and for SIMD later */
	for (i = 0, k =0; i < len; i++, k+=2) {
		R->data[i] += HEX_ME(array[k]) * 16;
		R->data[i] += HEX_ME(array[k + 1]);
	}

	if (odd)
		free(temp);

	//hex_dump("Long number (set_integer)", R->data, len ,32);

	return R;
}

integer*
set_integer_b16(uint8_t *array) {
	int16_t i, k;
	uint16_t len;
	uint16_t odd = 0;
	integer *R;
	uint8_t *temp;

	len = (strlen(array));
	odd = (len & 1);
	len = len/2 + odd;

	if (odd) {
		temp = malloc(len*2);
		temp[0] = '0';
		memcpy(&temp[1], array, len*2-1);
		array = temp;
	}

	R = malloc(sizeof(integer));
	R->data = malloc(len);
	R->size = len;

	memset(R->data, 0, len);

	/* Optimize for 8B,4B archs and for SIMD later */
	for (i = len-1, k =0; i>=0; i--, k+=2) {
		R->data[i] += HEX_ME(array[k]) * 16;
		R->data[i] += HEX_ME(array[k + 1]);
	}

	if (odd)
		free(temp);

	//hex_dump("Long number (set_integer b_16)", R->data, len ,32);

	return R;
}

integer *add_integer(integer *A, integer *B) {

	integer *R;
	uint16_t i;
	uint8_t carry;
	uint8_t *a, *b;

	R = malloc(sizeof(integer));
	R->size = (A->size > B->size ? A->size : B->size);
	R->data = malloc(R->size+1);
	a = malloc(R->size+1);
	b = malloc(R->size+1);

	memset(R->data, 0, R->size);
	memset(a, 0, R->size);
	memset(b, 0, R->size);

	memcpy(R->data, A->data, A->size);
	memcpy(a, A->data, A->size);
	memcpy(b, B->data, B->size);

	carry = 0;
	for (i = 0; i < R->size; i++) {
		uint8_t t_1 = a[i], t_2 = b[i];
		R->data[i] += b[i] + carry;
		if ((R->data[i] < t_1 || R->data[i] < t_2)) {
			carry = 1;
			if (i == R->size -1) {
				R->size = R->size+1;
			}
		}
		else
			carry = 0;
	}

	//hex_dump("Long number (set_integer b_16)", R->data, 4 ,32);

	free(a);
	free(b);

	return R;
}

integer *lshift(integer *A)
{
	integer *R;
	uint16_t size;
	uint16_t i;
	uint8_t carry = 0;

	if (A->data[A->size-1] & 0x80)
		size = A->size + 1;
	else
		size = A->size;

	R = malloc(sizeof(integer));
	R->data = malloc(size);
	R->size = size;

	R->data[0] = (A->data[0] << 1);
	carry = !!(A->data[0] & 0x80);

	for (i =1; i<A->size; i++) {
		R->data[i] = (A->data[i] << 1) + carry;
		carry = !!(A->data[i] & 0x80);
	}

	if (A->data[A->size-1] & 0x80)
		R->data[R->size-1] = 1;

	return R;
}

#define BIT_IN_STREAM(f, arg)	f->data[arg>>3] & (1 << (arg % 8))

integer *mult(integer *A, integer *B)
{
	integer *R;
	int i;
	uint16_t size;
	uint16_t ones = 0;
	integer **args;
	integer *factor;
	integer *temp;

//	factor = (A->size < B->size ? A : B); Optimize it for smaller factor, righ now get B
	factor = B;
	size = factor->size << 3;
	printf("\nMult size %hu", size);

	for (i = 0; i< size; i++) {
		if (BIT_IN_STREAM(factor, i)) {
			ones++;
		}
	}

	R = malloc(sizeof(integer));
	R->size = (size >> 3 ) * 2;
	R->data = malloc(sizeof(R->size));
	R->data = memcpy(R->data, A->data, A->size);

	for (i=0;i<ones - 1;i++) {
		temp = R;
		R = lshift(R);
		free(temp);
		if (BIT_IN_STREAM(B, i)) {
			temp = R;
			R = add_integer(R, A);
			free(temp);
		}
	}

	//hex_dump("Result", R->data, R->size ,32);

	free(args);
	return NULL;
}

/**
 * @brief
 */

int
set_integer_128_b16(uint8_t *array, struct Integer *A, int len) {
	int i, k;
	if (len == 0)
		len = 128;
	else if (len >128 || len < 0) {
		perror("");
		return -1;
	}

	for (i = len-1, k =0; i>=0; i--, k+=2) {
		A->data[i] += HEX_ME(array[k]) * 16;
		A->data[i] += HEX_ME(array[k + 1]);
	}
	hex_dump("Long number (set_integer b_16)", A->data, len , 32);
	A->size = len;
	return 0;
}

//int128_t int128_t_add(int128_t )
