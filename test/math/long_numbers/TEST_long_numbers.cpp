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

uint16_t karatsuba_treshold = 240;

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

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


}

void TEST_copy_bits_func()
{
    int128 A = "0x75A";
    int128 B;
    A.print_s("before");
    B.copy_bits(A, 1, 9);
    B.print_s("after");

}

#define INT int4096

int main(int argc, char *argv[])
{
    int i;
   //TEST_add_integer_128();
   //TEST_shift_integer();
   //TEST_cmp_integer();
   //TEST_mult_integer();
   //TEST_add_integer();
//    TEST_copy_bits_func();

 /*   int128 A = "0x10E";
    int128 B = "0x105"; */
    // 01 13 46
    /*int128 A = "0x21C";
    int128 B = "0x20A"; */
	// 04 4D 18

   /*int128 A = "0xB10";
   int128 B = "0xB10"; */
    // 7A 61 00

    /*int128 A = "0xC1B10";
    int128 B = "0xC1B10"; */
    // 92 8C 5C 61 00

    /*int128 A = "0x21321C1B10";
    int128 B = "0x343C1B10"; */
    // Error on online

    INT R;
    INT A = "0x23235435325FFF43543534252345423522345345345324534545523345235432534525232345675675475686568568"
            "568456856856856868561321232133213212332132132123221321C1B11"
            "0x23235435325FFF43543534252345423522345345345324534545523345235432534525232345675675475686568568"
            "568456856856856868561321232133213212332132132123221321C1B11";
    INT B = "0x2323532345342543234534252345234544354353454354445453545435454534532552421332123123123132132123"
            "231568568548568568568568456865865856865854422424324343C1B11"
            "0x23235435325FFF43543534252345423522345345345324534545523345235432534525232345675675475686568568"
            "568456856856856868561321232133213212332132132123221321C1B11";
    //INT A = "0x4F12B4A38A345323";
    //INT B = "0x12FFEAB53434BB11";

    A.print_s("A");
    B.print_s("B");

    uint64_t k_start = rdtsc();
    for (i = 0; i < 1000; i++) {
        R = karatsuba(A, B);
    }
    uint64_t k_end = rdtsc();

    R.print_s("karatsuba result");

    karatsuba_treshold = 9999;
    uint64_t r_start = rdtsc();
    for (i = 0; i < 1000; i++) {
        R = A * B;
    }
    uint64_t r_end = rdtsc();


    R.print_s("result");

    printf("\n");
    printf("\nKaratsuba time = \t%lu", k_end - k_start);
    printf("\nNormal time = \t\t%lu", r_end - r_start);
    printf("\n");
    return 0;
}
