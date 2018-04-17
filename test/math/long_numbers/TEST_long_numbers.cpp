#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Arus_dev_kit.h>

#include <iostream>

#include <CRYPTO_LIB_common.h>
#include <Integer.hpp>
#include "TEST_long_numbers_test_vectors.h"

#define INT_1	"1B0A"
#define INT_2	"0B"


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
    return 0;
}

static int __TEST_shift_vector(long_number_vector *vector)
{
    /*
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

    return result; */
}

static int __TEST_mult_vector(long_number_vector *vector)
{
    /*
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

    return result; */
}

static int __TEST_add_vector(long_number_vector *vector)
{
/*	bool result;
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

    return result; */
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
    int128 A = "0x336";
    int128 B = "0x240";

    A.print_s("A");
    B.print_s("B");

    //A = A + B;
    //A.print_s("A");

    std::cout << "A < B : " << (A < B);

    /*A.print_s("before");
    A |= 127;
    A.print_s("after"); */


}

extern int MW_COUNT;

#define PERF_DIV

#define __A 0xFF242423111//0xFF4332463246
#define __B 0xFF242423111//0xF785963454
#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

void TEST_sub()
{

    int128 A = "0x32463246";
    int128 B = "0xF785963";

    uint64_t a = 0x32463246;
    uint64_t b = 0xF785963;

    int i;

    uint64_t start = rdtsc();

    A = A - B;
    uint64_t end = rdtsc();


    start = rdtsc();
    A.print_s("A");
    end = rdtsc();

    printf("\n r = %lx", a - b);
}


void TEST_divide()
{

	//int128 A = "0x40";
	//int128 B = "0x10";
/* To check
    int128 A = "0xFE576234F13434";
    int128 B = "0xFA1000213DE";
*/
    int128 A = "0x101010101010101";
    int128 B = "0xFA10213DE";
   // int128 A = "0x1B";
   // int128 B = "0xF";

//	int128 A = "0x17";
//	int128 B = "0x6";

//	int128 A = "0x254";
//	int128 B = "0x28";

    uint64_t a = 0x101010101010101;
    uint64_t b = 0xFA10213DE;

    uint64_t r, m;

    uint64_t start = rdtsc();
    int i;
#ifdef PERF_DIV
    for (i = 0; i < 100000; i++) {
#endif
        r = a / b;

#ifdef PERF_DIV
    }
#endif
    uint64_t end = rdtsc();



    DIV_RESULT<128> res;

    start = rdtsc();
#ifdef PERF_DIV
    for (i = 0; i < 100000; i++)
#endif
        res = A.metoda_wielkanocna(B);
    end = rdtsc();

#ifdef PERF_DIV
    printf("\n cpu = %lu", end - start);
    printf("\n mw = %lu", end - start);
#endif

    printf("\n r = %lx m = %lx", a / b, a % b);
    res.ret.print("TEST result RET");
    res.mod.print("TEST result MOD");
}

void TEST_copy_bits_func()
{
    int128 A = "0x75A";
    int128 B;
    A.print_s("before");
    B.copy_bits(A, 1, 9);
    B.print_s("after");

    void test_fun();

}

void SETUP()
{
    int b = __builtin_cpu_is("intel");
    printf("\n intel = %d", b);

}

#define INT int8192

void TEST_add()
{
    int128 A = STR(__A);
    int128 B = STR(__B);

    uint64_t a = __A;
    uint64_t b = __B;

    (A + B).print("A + B");
    printf("\na + b %lx", a + b);

}
void TEST_increment()
{
    int128 A = STR(__A);

    uint64_t a = __A;

    A.print("A");
    A++;
    A.print("A++");
    a++;
    printf("\na++ %lx", a);

}

int main(int argc, char *argv[])
{
    int i;
    int128 A = "0xF1F5";
    int128 B = "0x13";

    int128 R;
    R.mod_exp(R);
    return 0;
}
