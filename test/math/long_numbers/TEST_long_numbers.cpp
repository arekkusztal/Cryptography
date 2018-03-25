#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Arus_dev_kit.h>

#include <CRYPTO_LIB_common.h>
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

static int __TEST_shift_vector(long_number_vector *vector)
{
#define DEBUG_1
	bool result;
	int128_t A = vector->A.data;
#ifdef DEBUG_1
    A.print_s("<----> DEFINITION: A");
    if (vector->op == LSH)
    	printf("\n shift left by = %hu", vector->lsh);
    else
    	printf("\n shift right by = %hu", vector->lsh);
#endif
    if (vector->op == LSH)
    	A <<= vector->lsh;
    else
    	A >>= vector->lsh;
#ifdef DEBUG_1
    A.print_s("<----> OPERATION:");
#endif
    if (result = (A == vector->R.data))
    	printf("\n%sTest %s SUCCESS%s", KGRN, vector->name, KNRM);
    else
    	printf("\n%sTest %s FAIL%s", KRED, vector->name, KNRM);

    return result;
}

static int __TEST_mult_vector(long_number_vector *vector)
{
	bool result;
	int128_t A = vector->A.data;
	int128_t B = vector->B.data;
#ifdef DEBUG_1
    A.print_s("<----> DEFINITION: A");
    B.print_s("<----> DEFINITION: B");
    printf("\n mult");
#endif
    A*=B;
#ifdef DEBUG_1
    A.print_s("<----> MULT:");
#endif

    if (result = (A == vector->R.data))
    	printf("\n%sTest %s SUCCESS%s", KGRN, vector->name, KNRM);
    else
    	printf("\n%sTest %s FAIL%s", KRED, vector->name, KNRM);

    return result;
}

static int __TEST_add_vector(long_number_vector *vector)
{
	bool result;
	int128_t A = vector->A.data;
	int128_t B = vector->B.data;
#ifdef DEBUG_1
    A.print_s("<----> DEFINITION: A");
    B.print_s("<----> DEFINITION: B");
    printf("\n mult");
#endif
    A+=B;
#ifdef DEBUG_1
    A.print_s("<----> ADD:");
#endif

    if (result = (A == vector->R.data))
    	printf("\n%sTest %s SUCCESS%s", KGRN, vector->name, KNRM);
    else
    	printf("\n%sTest %s FAIL%s", KRED, vector->name, KNRM);

    return result;
}

void TEST_shift_integer()
{
	foreach(vector, long_numbers_shift_vectors) {
        __TEST_shift_vector(vector);
    }
}

void TEST_mult_integer()
{
	foreach(vector, long_numbers_mult_vectors) {
        __TEST_mult_vector(vector);
    }
}

void TEST_add_integer()
{
	foreach(vector, long_numbers_add_vectors) {
        __TEST_add_vector(vector);
    }
}

void TEST_karatsuba()
{
	foreach(vector, long_numbers_add_vectors) {
        __TEST_add_vector(vector);
    }
}

void TEST_cmp_integer()
{
    int128_t A = "0x10E";
    int128_t B = "0x10E";
    printf("\n A == B : %d", A == &B);

}

int main(int argc, char *argv[])
{
   //TEST_add_integer_128();
   //TEST_shift_integer();
   //TEST_cmp_integer();
   //TEST_mult_integer();
   //TEST_add_integer();
	int128 A = "10FABB2";
	int256 B = "FF";
	int128 C = A + B;

	C.print_s("");
    printf("\n");
	return 0;
}
