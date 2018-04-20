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

enum SIGNEDNESS{
	SIGNED,
	UNSIGNED
};

template <uint16_t len_A, SIGNEDNESS sign>
struct DIV_RESULT;

template <uint16_t len, SIGNEDNESS sign>
class Integer
{
private:
	uint8_t __data[len] = { };
	uint16_t __len = 0;
	uint16_t __len_in_bits = 0;
	void __set_len_in_bits();

public:
	const SIGNEDNESS signedness = sign;
	const uint64_t precision = len;
	/* < Constructors */
	Integer() = default;
	Integer<len, sign>(uint8_t *);
	Integer<len, sign>(const char *);
	/* < Operators */
	/* < ---- *< Assignement */
	Integer<len, sign> operator=(Integer<len, sign>);
	/* < ---- *< Arithmetic */
	Integer<len, sign> operator+(const Integer<len, sign>&);
	Integer<len, sign>& operator++();
	Integer<len, sign>& operator++(int);
	Integer<len, sign>& operator+=(const Integer<len, sign>&);
	Integer<len, sign> operator-(const Integer<len, sign>&);
	Integer<len, sign> operator*(const Integer<len, sign>&);
	Integer<len, sign> operator/(const Integer<len, sign>&);
	Integer<len, sign> operator%(const Integer<len, sign>&);
	Integer<len, sign> karatsuba(const Integer<len, sign>&);
	Integer<len, sign> mod_exp(const Integer<len, sign>&, const Integer<len, sign>&);
	Integer<len, sign> mod_inv(const Integer<len, sign>&, const Integer<len, sign>&);
	DIV_RESULT<len, sign> metoda_wielkanocna(const Integer<len, sign>&);

	/* < ---- *< Shift operators */
	Integer<len, sign>& operator<<=(uint16_t shift);
	Integer<len, sign> operator<<(uint16_t shift);
	Integer<len, sign>& operator>>=(uint16_t shift);
	Integer<len, sign> operator>>(uint16_t shift);
	/* < ---- *< Logical */
	Integer<len, sign>& operator&(Integer<len, sign>& mask);
	Integer<len, sign>& operator|=(uint16_t pos);
	/* < ---- *< Comparision */
	bool operator==(Integer<len, sign>);
	bool operator<(const Integer<len, sign>&);
	bool operator>(const Integer<len, sign>&);

	template<uint16_t __len, SIGNEDNESS __sign>
	Integer<__len, __sign> integer_cast(Integer<len, sign>);
	/* <Len functions */
	void copy_bits(Integer A, uint16_t start, uint16_t end);

	/* < Debug funcs */
	void print(const char * str);
	void print_s(const char * str);
};

template <uint16_t len_A, SIGNEDNESS sign>
struct DIV_RESULT
{
    Integer<len_A, sign> ret;
    Integer<len_A, sign> mod;
};

template class Integer<128, SIGNED>;
template class Integer<256, SIGNED>;
template class Integer<512, SIGNED>;
template class Integer<4096, SIGNED>;
template class Integer<8192, SIGNED>;

using int128_t = Integer<128, SIGNED>;
using int256_t = Integer<256, SIGNED>;
using int512_t = Integer<512, SIGNED>;
using int4096_t = Integer<4096, SIGNED>;
using int8192_t = Integer<8192, SIGNED>;


#endif /* LONG_NUMBERS_H_ */
