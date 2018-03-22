#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Arus_dev_kit.h>

#include <long_numbers.hpp>
#include "TEST_long_numbers_test_vectors.h"

#define INT_1	"1B0A"
#define INT_2	"0B"



template <uint16_t len_t>
class A
{
public:
    A();
    uint16_t len = len_t;

};

template <uint16_t len_t>
A<len_t>::A() { };

using int256_t = A<256>;
using int512_t = A<512>;
using int1024_t = A<1024>;

int TEST_add_integer_128()
{
   int128_t A = "0x10E";
   int128_t B = "0x105";
  // A-=B;
  // A.print();
   int i;
   A.print_s("A");
   B.print_s("B");
   A.karatsuba(B);

    return 0;
}

void TEST_shift_integer()
{
    int128_t A = "0x10E";
    A.print_s("A");
    A <<=120;
    A.print_s("A <<= 120");
    A >>=120;
    A.print_s("A >>= 120");
}

int main(int argc, char *argv[])
{
   //TEST_add_integer_128();
   TEST_shift_integer();
	return 0;
}
