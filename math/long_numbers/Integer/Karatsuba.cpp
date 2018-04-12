#include <Integer.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include <CRYPTO_LIB_common.h>
#include <Arus_dev_kit.h>

#define __DEBUG_

#ifdef __DEBUG
#define DEBUG_PRINTF(str) printf(str);
#define DEBUG_PRINT(arg,str) arg.print_s(str);
#else
#define DEBUG_PRINTF(str)
#define DEBUG_PRINT(arg,str)
#endif

#define KARATSUBA_BYTE_OFFSET 120
template <uint16_t len>
Integer<len> Integer<len>::karatsuba(const Integer<len>& A, const Integer<len>& B)
{
    Integer<len> ret;
/*    if (A.__len_in_bits + B.__len_in_bits > A.precision) {
        printf("\nINFO: potential overflow = %hu", A.__len_in_bits + B.__len_in_bits);
        return ret;
    }

    uint16_t __chosen_one, __b;

    Integer<len> Z_0, Z_1, Z_2;
    Integer<len> x_0, x_1, y_0, y_1;

    if (KARATSUBA_BYTE_OFFSET >= (A.__len)) {
     //   printf("\nINFO: Leaving Karatsuba A.__len/2 = %hu", A.__len >> 1);
        return A * B;
    }
    __chosen_one = (A.__len - KARATSUBA_BYTE_OFFSET) << 3;
    __b = __chosen_one << 1;
    x_0.copy_bits(A, __chosen_one, A.__len_in_bits);

    DEBUG_PRINT(x_0, "x_0");
    x_1.copy_bits(B, __chosen_one, B.__len_in_bits);
    DEBUG_PRINT(x_1, "x_1");
    y_0.copy_bits(A, 0, __chosen_one);
    DEBUG_PRINT(y_0, "y_0");
    y_1.copy_bits(B, 0, __chosen_one);
    DEBUG_PRINT(y_1, "y_1");
    Z_2 = x_0 * x_1;
    DEBUG_PRINT(Z_2, "Z_2");
    Z_0 = y_0 * y_1;
    DEBUG_PRINT(Z_0, "Z_0");
    Z_1 = (x_0 + y_0) * (x_1 + y_1) - Z_0 - Z_2;
    DEBUG_PRINT(Z_1, "Z_1");
    ret = (Z_2 << __b) + (Z_1 << __chosen_one) + Z_0; */

    return ret;
}


