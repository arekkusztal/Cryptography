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

	hex_dump("Long number", R->data, len ,32);

	return R;
}

integer *add_integer(integer *A, integer *B) {

	integer *R;
	uint16_t i;
	uint8_t carry;


//	hex_dump("Addition", A->data, A->size ,32);
//	hex_dump("Addition", B->data, B->size ,32);

	R = malloc(sizeof(integer));
	R->size = A->size + 1;
	R->data = malloc(R->size+1);

	memcpy(R->data, A->data, A->size);

	carry = 0;
	for (i =0 ;i< R->size ; i++) {
		uint8_t t_1 = A->data[i], t_2 = B->data[i];
		R->data[i] += B->data[i] + carry;
		if (R->data[i] <= t_1 || R->data[i] <= t_2)
			carry = 1;
		else
			carry = 0;
	}


	return R;
}

uint8_t I_1[4] = { 0xFF, 0xFC, 0xFF, 0x80 };
uint8_t I_2[4] = { 0xFF, 0xFC, 0xFF, 0x80 };



int main(int argc, char *argv[])
{
	int i;
	integer *A, *B, *R;
	A = set_integer_b16("8001FFCDEF5430875948574985743985749385743987532895783275983279");
	B = set_integer_b16("CAB575711AF24124879847219882374983724983279238479328749328749238");
	R = malloc(sizeof(R));
	uint8_t carry = 0;

	R = add_integer(A, B);




	hex_dump("Addition", R->data, R->size ,32);
	printf("\naddition int: %d",*(int *)&I_1[0]);



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

