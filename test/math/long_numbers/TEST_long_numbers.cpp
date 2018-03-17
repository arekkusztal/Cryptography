#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Arus_dev_kit.h>

#include <long_numbers.hpp>
#include "TEST_long_numbers_test_vectors.h"

#define INT_1	"1B0A"
#define INT_2	"0B"

int TEST_add_integer_128()
{
	int128_t A = "0xAB1F2BC";
	int128_t B = "0xF1FF2BC";
	int128_t C = "0xF1241EF231789";
	A += C;
	//C<<=1;
	A.print();
}

int main(int argc, char *argv[])
{
	TEST_add_integer_128();
	return 0;
}
