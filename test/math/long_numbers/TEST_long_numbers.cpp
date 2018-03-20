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
   int128_t A = "0x21C";
   int128_t B = "0x20A";
   int i;
   A.print_s("A");
   B.print_s("B");
   A.karatsuba(B);


}

int main(int argc, char *argv[])
{
	TEST_add_integer_128();
	return 0;
}
