#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <long_numbers.h>
#include "TEST_long_numbers_test_vectors.h"

int main(int argc, char *argv[])
{
	int i;
	integer *A, *B, *R;
	A = set_integer_b16("B");
	B = set_integer_b16("D");
	R = malloc(sizeof(R));
	uint8_t carry = 0;

	R = add_integer(A, B);
	R = mult(A, B);

	//R = lshift(A);
	//hex_dump("Addition", R->data, R->size ,32);

	return 0;
}
