/*
 * long_numbers.h
 *
 *  Created on: Mar 5, 2018
 *      Author: arek67
 */

#ifndef LONG_NUMBERS_H_
#define LONG_NUMBERS_H_

#include <stdint.h>
#include <Arus_dev_kit.h>

#define DEBUG

typedef struct Integer_2 {
	uint8_t *data;
	uint16_t size;
} integer;

class int128_fast_t;

class Int {
public:
	uint16_t __len = 0;
	uint16_t __len_in_bits = 0;
	virtual void __set_len_in_bits() = 0;
public:
#ifdef DEBUG
	virtual void print() = 0;
#endif
};

class int128_t : public Int {
#define PRECISION 128
	uint8_t __data[PRECISION] = { };
	inline void __set_len_in_bits() override;
public:
	enum ERROR_CODE {
	   noerror = 0,
	   overflow,
	   negative,
	   potential_overflow,
	   too_small_to_bother,
	};
	const uint16_t precision = PRECISION;
   enum ERROR_CODE error_code = noerror;
	int128_t() = default;
	int128_t(const int128_t& int128_t);
	int128_t(uint8_t *);
	int128_t(const char *);
	int128_t(int128_fast_t);
	int128_t(int128_t, uint16_t start, uint16_t end);
	int128_t operator=(int128_t);   
	int128_t operator+(Int *);
	int128_t operator=(const char *);
	int128_t operator=(int128_fast_t);
	int128_t operator+=(int128_t);
	int128_t operator<<=(uint16_t);
	int128_t operator>>=(uint16_t);
   int128_t& operator*=(int128_t);
	int128_t karatsuba(int128_t);
   int128_t& operator-=(int128_t);
   bool operator==(int128_t *);

	int copy_bits(int128_t, uint16_t start, uint16_t end);
	void copy_bits_1(uint16_t start, uint16_t end);

	~int128_t() = default;

	void print() override;
	void print_s(const char * str);
};

class int128_fast_t {
#define PRECISION 128

};

integer*
set_integer_b16(uint8_t *array);

int
set_integer_128_b16(uint8_t *array, struct Integer_2 *A, int len);

int 
sub_integer_128(uint8_t *A, uint8_t *B, uint8_t *R);

int
add_integer_128(uint8_t *A, uint8_t *B, uint8_t *R);

integer*
set_integer(uint8_t *array);

integer*
add_integer(integer *A, integer *B);

integer*
lshift(integer *A);

integer*
mult(integer *A, integer *B);

#endif /* LONG_NUMBERS_H_ */
