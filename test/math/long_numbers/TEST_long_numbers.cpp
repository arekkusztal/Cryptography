#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Arus_dev_kit.h>

#include <long_numbers.hpp>
#include "TEST_long_numbers_test_vectors.h"

#define INT_1	"1B0A"
#define INT_2	"0B"
/*
int TEST_add_integer_128()
{
	struct Integer A, B;
	uint8_t placeholder_1[512], placeholder_2[512];
	memset(placeholder_1, 0, 512);
	set_integer_128_b16(INT_1, &A, 2);
	printf("\nadd integer");
	return 0;
}

*/

int main(int argc, char *argv[])
{
	int128_t a = "0xAB1F2BC";
	a.print();
	return 0;
}
