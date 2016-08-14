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

	hex_dump("Long number (set_integer)", R->data, len ,32);

	return R;
}

integer *add_integer(integer *A, integer *B) {

	integer *R;
	uint16_t i;
	uint8_t carry;
	/* To make it really easy */
	uint8_t *a, *b;

	R = malloc(sizeof(integer));
	R->size = (A->size > B->size ? A->size : B->size) + 1;
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
	for (i =0 ;i< R->size ; i++) {
		uint8_t t_1 = a[i], t_2 = b[i];
		R->data[i] += b[i] + carry;
		if ((R->data[i] <= t_1 || R->data[i] <= t_2) && t_1 && t_2)
			carry = 1;
		else
			carry = 0;
	}

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


int main(int argc, char *argv[])
{
	int i;
	integer *A, *B, *R;
	A = set_integer_b16("8001");
	B = set_integer_b16("8001");
	R = malloc(sizeof(R));
	uint8_t carry = 0;

	R = add_integer(A, B);

	//R = lshift(A);
	hex_dump("Addition", R->data, R->size ,32);
	return 0;
}






/* x86
 *
 * /*
	asm volatile(
			"clc;"
			"adc %[in], %[out];"
			: [out] "=m" (I_1[0])
			: [in] "r" (I_2[0])
	);

	for (i = 1; i<= 3; i++) {
		asm volatile(
				"adc %[in], %[out];"
				: [out] "=m" (I_1[i])
				: [in] "r" (I_2[i])
		);
	} */


/*	uint8_t R[5] = { 0 };
	memcpy(R, A->data, A->size); */


/*	for (i =0 ;i< 5 ; i++) {
		uint8_t t_1 = I_1[i], t_2 = I_2[i];
		R[i] += I_2[i] + carry;
		if (R[i] <= t_1 || R[i] <= t_2)
			carry = 1;
		else
			carry = 0;
	} */

/*	for (i =0 ;i< A->size+1 ; i++) {
		uint8_t t_1 = A->data[i], t_2 = B->data[i];
		R[i] += B->data[i] + carry;
		if (R[i] <= t_1 || R[i] <= t_2)
			carry = 1;
		else
			carry = 0;
	} */

