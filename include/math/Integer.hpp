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
using BNLib_int_size = uint16_t;

template <uint16_t len_A>
struct DIV_RESULT;

template <uint16_t len>
class Integer
{
private:
	uint8_t __data[len] = { };
	uint16_t __len = 0;
	uint16_t __len_in_bits = 0;
	void __set_len_in_bits();
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
	Integer<len> operator+(const Integer<len>&);
	Integer<len>& operator++();
	Integer<len>& operator++(int);
	Integer<len>& operator+=(const Integer<len>&);
	Integer<len> operator-(const Integer<len>&);
	Integer<len> operator*(const Integer<len>&);
	Integer<len> operator/(const Integer<len>&);
	Integer<len> karatsuba(const Integer<len>& B);
	DIV_RESULT<len> metoda_wielkanocna(const Integer<len>& B);

	/* < ---- *< Shift operators */
	Integer<len>& operator<<=(uint16_t shift);
	Integer<len> operator<<(uint16_t shift);
	Integer<len>& operator>>=(uint16_t shift);
	Integer<len> operator>>(uint16_t shift);
	/* < ---- *< Logical */
	Integer<len>& operator&(Integer<len>& mask);
	Integer<len>& operator|=(uint16_t pos);
	/* < ---- *< Comparision */
	bool operator==(Integer<len>);
	bool operator<(const Integer<len>&);
	bool operator>(const Integer<len>&);

	template<uint16_t __len>
	Integer<__len> integer_cast(Integer<len>);
	/* <Len functions */
	void copy_bits(Integer A, uint16_t start, uint16_t end);

	/* < Debug funcs */
	void print(const char * str);
	void print_s(const char * str);
};

template <uint16_t len_A>
struct DIV_RESULT
{
    Integer<len_A> ret;
    Integer<len_A> mod;
};

template class Integer<128>;
template class Integer<256>;
template class Integer<512>;
template class Integer<4096>;
template class Integer<8192>;

using int128 = Integer<128>;
using int256 = Integer<256>;
using int512 = Integer<512>;
using int4096 = Integer<4096>;
using int8192 = Integer<8192>;


#endif /* LONG_NUMBERS_H_ */
