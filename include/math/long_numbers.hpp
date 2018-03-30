/*
 * long_numbers.hpp
 *
 *  Created on: Mar 5, 2018
 *      Author: Arek Kusztal
 */

#ifndef LONG_NUMBERS_H_
#define LONG_NUMBERS_H_

#include <stdint.h>
#include <Arus_dev_kit.h>
#include <CRYPTO_LIB_common.h>

extern uint16_t karatsuba_treshold;

template <uint16_t len>
class Integer
{
public:
	uint8_t __data[len] = { };
	uint16_t __len = 0;
	uint16_t __len_in_bits = 0;
public:

	const uint64_t precision = len;
	/* < Constructors */
	Integer() = default;
	Integer<len>(uint8_t *);
	Integer<len>(const char *);
	/* < Operators */
	/* < ---- *< Assignement */
	Integer<len> operator=(Integer<len>);
   /* < ---- *< Arithmetic */

   /* < ---- *< Shift operators */
   Integer<len>& operator<<=(uint16_t shift);
   Integer<len>& operator>>=(uint16_t shift);
	/* <Len functions */
   void __set_len_in_bits();
   void copy_bits(Integer A, uint16_t start, uint16_t end);

	/* < Debug funcs */
	void print();
   void print_s(const char * str);
};

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> operator*(const Integer<len_A> &A, const Integer<len_B>& B);

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> operator*(const Integer<len_A> &&A, const Integer<len_B>& B);

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> karatsuba(const Integer<len_A>& A, const Integer<len_B>& B);

using int16 = Integer<16>;
using int32 = Integer<32>;
using int128 = Integer<128>;
using int256 = Integer<256>;
using int512 = Integer<512>;
using int4096 = Integer<4096>;
using int8192 = Integer<8192>;


#endif /* LONG_NUMBERS_H_ */
