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
   int128_t A = "0x40";//0xAB1F2BC";
  // int128_t B = "0x123FF";
  // int128_t C = "0x1";
   //A += C;
  // int128_t D = A;
  // C<<=16;

   //A.print();
  // A*=B;


   A.print();
}

int main(int argc, char *argv[])
{
	TEST_add_integer_128();
	return 0;
}