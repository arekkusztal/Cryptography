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
#include <CRYPTO_LIB_common.h>


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
	int128_t operator=(unsigned char *);
	int128_t operator=(int128_fast_t);
	int128_t operator+=(int128_t);
	int128_t operator<<=(uint16_t);
	int128_t operator>>=(uint16_t);
   int128_t& operator*=(int128_t);
	int128_t karatsuba(int128_t);
   int128_t& operator-=(int128_t);
   bool operator==(int128_t *);
   bool operator==(unsigned char *);

	int copy_bits(int128_t, uint16_t start, uint16_t end);
	void copy_bits_1(uint16_t start, uint16_t end);

	~int128_t() = default;

	void print() override;
	void print_s(const char * str);
};

class int128_fast_t {
#define PRECISION 128

};

template <uint16_t len>
class Integer
{
public:
	uint8_t __data[len] = { };
public:

	const uint64_t precision = len;
	/* < Constructors */
	Integer() = default;
	Integer<len>(uint8_t *);
	Integer<len>(const char *);
	/* < Operators */
	Integer<len> operator=(Integer<len>);

	uint16_t __len = 0;
	uint16_t __len_in_bits = 0;
	void __set_len_in_bits();

	/* < Debug funcs */
	void print();
	void print_s(const char * str);
};

template <uint16_t len>
Integer<len>::Integer(uint8_t *number)
{
	uint16_t __len, i, prefix;

	__len = strlen((const char *)number);
	if (__len > 128)
		return;

	i = 0;
	if (number[0] == '0' && number[1] == 'x')
		prefix = 2;
	else
		prefix = 0;

	while (i < __len - prefix) {
		/*
		 * TODO
		 * check if number[] is hex
		 */
		__data[(i & (~1)) >> 1] += (i & 1) ?
				(HEX_ME(number[__len - i - 1]) << 4) :
					HEX_ME(number[__len - i - 1]);
		i++;
	}

	this->__len = ((__len - prefix) >> 1) + (__len & 1);
   __set_len_in_bits();
}

template <uint16_t len>
Integer<len>::Integer(const char *number)
{
	uint16_t __len, i, prefix;

	__len = strlen((const char *)number);
	if (__len > 128)
		return;

	i = 0;
	if (number[0] == '0' && number[1] == 'x')
		prefix = 2;
	else
		prefix = 0;

	while (i < __len - prefix) {
		/*
		 * TODO
		 * check if number[] is hex
		 */
		__data[(i & (~1)) >> 1] += (i & 1) ?
				(HEX_ME(number[__len - i - 1]) << 4) :
					HEX_ME(number[__len - i - 1]);
		i++;
	}

	this->__len = ((__len - prefix) >> 1) + (__len & 1);
   __set_len_in_bits();
}

template <uint16_t len>
Integer<len> Integer<len>::operator=(Integer<len> A)
{
    memcpy(this, &A, sizeof(*this));
}

template <uint16_t len>
void Integer<len>::__set_len_in_bits()
{
    int i;
    if (this->__len == 0) {
    	this->__len_in_bits = 0;
    	return;
    }

    for (i = 7; i >= 0; i--) {
        if ((this->__data[this->__len - 1] >> i) & 1) {
            this->__len_in_bits = ((this->__len - 1) << 3) + i + 1;
            return;
        }
    }
    this->__len_in_bits = ((this->__len - 1) << 3) + i + 1;
}

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> integer_cast(Integer<len_B> B)
{
	Integer<len_A> ret;

	return ret;
}

template <uint16_t len>
void Integer<len>::print()
{
   hex_dump("int128", this->__data, this->__len, 16);
}

template <uint16_t len>
void Integer<len>::print_s(const char * str)
{
    int i;
    printf("\n<");
    for (i = 0; i < 40; i++)
        printf("-");
    printf("\n%s %s %s", KNRM, str, KNRM);
   	   printf("\n | len = %s%hu%s | leninbits = %s%hu%s |", KNRM, this->__len, KNRM, KNRM,this->__len_in_bits, KNRM);
    bit_dump_s(this->__data, this->__len);

    for (i = 0; i < 40; i++)
        printf("-");
    printf(">");

}

using int128 = Integer<128>;
using int256 = Integer<256>;


#endif /* LONG_NUMBERS_H_ */
