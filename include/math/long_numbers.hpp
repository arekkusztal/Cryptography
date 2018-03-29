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
   memcpy(this->__data, A.__data, A.__len);
	this->__len = A.__len;
   this->__len_in_bits = A.__len_in_bits;
}

/*
 * ********** Arithmetic operators  **********
 */
/*
 * @brief Add operator, works when len of A is equal or bigger than len of B
 *
 */

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> operator+(Integer<len_A>& A, Integer<len_B> B)
{
	Integer<len_A> ret;
	uint16_t i, __max_of_two, __complement;
	uint8_t carry;

	carry = 0;
	i = 0;
	__complement = 0;
	__max_of_two = A.__len >= B.__len ?
			A.__len : B.__len;

	if (__builtin_expect(len_A < len_B, 0))
		throw;
	if (__builtin_expect(len_A > len_B, 0)) {
		__complement = __max_of_two;
		__max_of_two = len_B >> 3;
	}

	while (i < __max_of_two)
	{
		ret.__data[i] = A.__data[i] + B.__data[i] + carry;
		if (__builtin_expect((A.__data[i] && B.__data[i]), 1)) {
			if (ret.__data[i] < A.__data[i] || ret.__data[i] < B.__data[i])
				carry = 1;
			else
				carry = 0;
		} else if ((A.__data[i] == 0xFF || B.__data[i] == 0xFF) && carry)
			carry = 1;
		else
			carry = 0;
		i++;
	}

	while (i < __complement)
	{
		ret.__data[i] = A.__data[i] + carry;
		if (__builtin_expect((A.__data[i]), 1)) {
			if (ret.__data[i] < A.__data[i])
				carry = 1;
			else
				carry = 0;
		} else if (A.__data[i] == 0xFF && carry)
			carry = 1;
		i++;
	}

	ret.__len = __complement ? __complement : __max_of_two;
	if (carry) {
		ret.__data[i] = 1;
		ret.__len += 1;
		if (ret.__len > (len_A >> 3)) {
			ret.__len -= (len_A >> 3);
		}
	}
   ret.__set_len_in_bits();

   return ret;
}

template <uint16_t len_A, uint16_t len_B>
Integer<len_A>& operator+=(Integer<len_A>& A, Integer<len_B> B)
{
   Integer<len_A> ret;
   uint16_t i, __max_of_two, __complement;
   uint8_t carry;

   carry = 0;
   i = 0;
   __complement = 0;
   __max_of_two = A.__len >= B.__len ?
         A.__len : B.__len;

   if (__builtin_expect(len_A < len_B, 0))
      throw;
   if (__builtin_expect(len_A > len_B, 0)) {
      __complement = __max_of_two;
      __max_of_two = len_B >> 3;
   }

   while (i < __max_of_two)
   {
      uint8_t __tmp_A = A.__data[i];
      A.__data[i] = A.__data[i] + B.__data[i] + carry;
      if (__builtin_expect((A.__data[i] && B.__data[i]), 1)) {
         if (A.__data[i] < __tmp_A || A.__data[i] < B.__data[i])
            carry = 1;
         else
            carry = 0;
      } else if ((__tmp_A == 0xFF || B.__data[i] == 0xFF) && carry)
         carry = 1;
      else
         carry = 0;
      i++;
   }

   while (i < __complement)
   {
      uint8_t __tmp_A = A.__data[i];
      A.__data[i] = A.__data[i] + carry;
      if (__builtin_expect((A.__data[i]), 1)) {
         if (A.__data[i] < __tmp_A)
            carry = 1;
         else
            carry = 0;
      } else if (__tmp_A == 0xFF && carry)
         carry = 1;
      i++;
   }

   A.__len = __complement ? __complement : __max_of_two;
   if (carry) {
      A.__data[i] = 1;
      A.__len += 1;
      if (A.__len > (len_A >> 3)) {
         A.__len -= (len_A >> 3);
      }
   }
   ret.__set_len_in_bits();

   return A;
}

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> operator-(Integer<len_A> A, Integer<len_B> B)
{
    Integer<len_A> ret;
    uint16_t i, k, __max_of_two;
    uint8_t borrow, __b;

    __max_of_two = A.__len >= B.__len ?		\
          A.__len : B.__len;

    borrow = 0;

    for (i = 0; i < A.__len;i++) {
        if (!A.__data[i])
            continue;

        A.__data[i] -= borrow;
        if (A.__data[i] < B.__data[i]) {
            borrow = 1;
            uint16_t ext_1 = A.__data[i];
            ext_1 += 0x100;
            ext_1 -= B.__data[i];
            ret.__data[i] = ext_1;
        }
        else {
            ret.__data[i] = A.__data[i] - B.__data[i];
            borrow = 0;
        }
    }

    return ret;
}

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> operator*(Integer<len_A> A, Integer<len_B> B)
{
   Integer<len_A> ret;
   Integer<len_A> __temp, __shifted;
   uint16_t i, k, __min_of_two, __final_len;
   uint8_t __a_is_smaller;

   __temp.__len = 1;
   __temp.__len_in_bits = 8;
   __final_len = ((A.__len_in_bits + B.__len_in_bits - 1) >> 3) + 1;


   if (A.__len <= B.__len) {
       __shifted = B;
       __a_is_smaller = true;
   }
   else {
       __shifted = A;
       __a_is_smaller = false;
   }

   if (__a_is_smaller) {
       for (i = 0; i < A.__len << 3; i++) {
           if ( (A.__data[i >> 3] >> (i & 0x7)) & 1) {
               __temp += __shifted;

           }
           __shifted <<= 1;
       }
   }
   else {
        for (i = 0; i < B.__len << 3; i++) {
            if ( (B.__data[i >> 3] >> (i & 0x7)) & 1) {
                __temp += __shifted;
            }
            __shifted <<= 1;
        }
   }

   ret = __temp;
   ret.__len = __final_len;
   ret.__set_len_in_bits();

   if (ret.__len_in_bits > ret.precision) {
       ret.__len_in_bits = ret.precision;
       ret.__len = ret.precision >> 3;
   }

   return ret;
}

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> karatsuba(Integer<len_A> A, Integer<len_B> B)
{
#define OFFSET_CONSTANT 1
    Integer<len_A> ret;
    uint16_t __chosen_one, __b;

    Integer<len_A> Z_0, Z_1, Z_2;
    Integer<len_A> x_0, x_1, y_0, y_1;

    __chosen_one = A.__len_in_bits - OFFSET_CONSTANT;
    __b = __chosen_one << 1;
    x_0.copy_bits(A, __chosen_one - 1, A.__len_in_bits);
    x_0.print_s("x_0");
    x_1.copy_bits(B, __chosen_one - 1, B.__len_in_bits);
    x_0.print_s("x_1");

    y_0.copy_bits(A, 0, __chosen_one - 2);
    y_0.print_s("y_0");

    y_1.copy_bits(B, 0, __chosen_one - 2);
    y_1.print_s("y_1");

    Z_2 = x_0;
    Z_2 = Z_2 * x_1;
    Z_2.print_s("Z_2");


    Z_0 = y_0;
    Z_0 = Z_0 * y_1;
    Z_0.print_s("Z_0");

    Z_1 = x_0;

    Z_1 += y_0;

    Z_1 += y_1;

    Z_1 = Z_1 * x_1;

    Z_1 = Z_1 - Z_2;

    x_0 = x_0 - Z_0;

    Z_2 <<= __b - 1;
    Z_1 <<= __chosen_one - 1;

    Z_2 += Z_1;
    Z_2 += Z_0;
    Z_2.print_s("Z_2");

    return ret;
}

/*
 * ********** Bit shift operators  **********
*/

template <uint16_t len>
Integer<len> operator<<(Integer<len> A, uint16_t shift)
{
   Integer<len> ret;
   int i;
   uint16_t add_len, org_shift;

   shift &= (len - 1);
   org_shift = shift;
   add_len = 0;

   for (i = 0; i < (shift & 0x7); i++) {
        if ( (A.__data[A.__len - 1] >> (7 - i)) & 1)
            add_len = 1;
   }

   i = 0;
   for (i = len - 1; i >= (shift >> 3); i--) {
      ret.__data[i] = A.__data[i - (shift >> 3)];
   }
   for (i = (shift >> 3) - 1; i >= 0; i--) {
      ret.__data[i] = 0;
   }
   i = 0;
   shift &= 0x7;
   if (shift && shift < 8) {

      uint8_t __prev_left = A.__data[i] >> (8 - shift);
      ret.__data[i] <<= shift;
      uint8_t __curr;

      while (i < A.__len + (org_shift >> 3)) {
         i++;
         __curr = A.__data[i];
         ret.__data[i] = A.__data[i] << shift | __prev_left;
         __prev_left = __curr >> (8 - shift);
      }
   }

   ret.__len = (A.__len + ((org_shift >> 3) + add_len)) > (A.precision >> 3) ?
               (A.precision >> 3) : (A.__len + ((org_shift >> 3) + add_len));
   ret.__set_len_in_bits();
   return ret;
}

template <uint16_t len>
Integer<len>& Integer<len>::operator<<=(uint16_t shift)
{
   int i;
   uint16_t add_len, org_shift;

   shift &= ~0x80;
   org_shift = shift;
   add_len = 0;

   for (i = 0; i < (shift & 0x7); i++) {
        if ( (this->__data[this->__len - 1] >> (7 - i)) & 1)
            add_len = 1;
   }

   i = 0;
   for (i = 15; i >= (shift >> 3); i--) {
      this->__data[i] = this->__data[i - (shift >> 3)];
   }
   for (i = (shift >> 3) - 1; i >= 0; i--) {
      this->__data[i] = 0;
   }
   i = 0;
   shift &= 0x7;
   if (shift && shift < 8) {

      uint8_t __prev_left = this->__data[i] >> (8 - shift);
      this->__data[i] <<= shift;
      uint8_t __curr;

      while (i < this->__len + (org_shift >> 3)) {
         i++;
         __curr = this->__data[i];
         this->__data[i] = this->__data[i] << shift | __prev_left;
         __prev_left = __curr >> (8 - shift);
      }
   }

   this->__len = (this->__len + ((org_shift >> 3) + add_len)) > (this->precision >> 3) ?
               (this->precision >> 3) : (this->__len + ((org_shift >> 3) + add_len));
   __set_len_in_bits();
   return *this;
}

template <uint16_t len>
Integer<len> operator>>(Integer<len> A, uint16_t shift)
{    
   Integer<len> ret;
   int i;
   uint16_t sub_len, org_shift;

   shift &= (len - 1);
   org_shift = shift;
   sub_len = 1;

   if (shift >= A.__len_in_bits) {
      /* TODO: Check if to clear as empty ret */
       memset(ret.__data, 0, ret.precision >> 3);
       ret.__len = 0;
       ret.__len_in_bits = 0;
       return ret;
   }

   for (i = 0; i < 8 - (shift & 0x7); i++) {
        if ( (A.__data[A.__len - 1] >> (7 - i)) & 1)
            sub_len = 0;
   }

   i = 0;
   for (i = 0; i < len - (shift >> 3); i++) {
      ret.__data[i] = A.__data[i + (shift >> 3)];
   }
   for (i = (len - 1) - (shift >> 3); i < 16; i++) {
      ret.__data[i] = 0;
   }
   i = A.__len - 1;
   shift &= 0x7;
   if (shift < 8) {
      uint8_t __prev_right = A.__data[i];
      ret.__data[i] >>= shift;
      uint8_t __curr;

      while (i >= 0) {
         i--;
         __curr = A.__data[i];
         ret.__data[i] = A.__data[i] >> shift | (__prev_right << (8 - shift));
         __prev_right = __curr;
      }
   }

   ret.__len = A.__len - (org_shift >> 3) + sub_len;
   ret.__set_len_in_bits();

   return ret;
}

template <uint16_t len>
Integer<len>& Integer<len>::operator>>=(uint16_t shift)
{
   int i;
   uint16_t sub_len, org_shift;

   shift &= ~0x80;
   org_shift = shift;
   sub_len = 1;

   if (shift >= this->__len_in_bits) {
      /* TODO: Optimize to size */
       memset(this->__data, 0, this->precision >> 3);
       this->__len = 0;
       this->__len_in_bits = 0;
       return *this;
   }

   for (i = 0; i < 8 - (shift & 0x7); i++) {
        if ( (this->__data[this->__len - 1] >> (7 - i)) & 1)
            sub_len = 0;
   }

   i = 0;
   for (i = 0; i < 16 - (shift >> 3); i++) {
      this->__data[i] = this->__data[i + (shift >> 3)];
   }
   for (i = 16 - (shift >> 3); i < 16; i++) {
      this->__data[i] = 0;
   }
   i = this->__len - 1;
   shift &= 0x7;
   if (shift < 8) {
      uint8_t __prev_right = this->__data[i];
      this->__data[i] >>= shift;
      uint8_t __curr;

      while (i >= 0) {
         i--;
         __curr = this->__data[i];
         this->__data[i] = this->__data[i] >> shift | (__prev_right << (8 - shift));
         __prev_right = __curr;
      }
   }

   this->__len -= (org_shift >> 3) + sub_len;
   __set_len_in_bits();
}

/*
 * ********** Misc member functions  **********
*/

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
    //this->__len_in_bits = ((this->__len - 1) << 3) + i + 1;
    this->__len -= 1;
    this->__set_len_in_bits();
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

template <uint16_t len>
void Integer<len>::copy_bits(Integer A, uint16_t start, uint16_t end)
{
   *this = A;
   *this <<= (A.precision - end);
   *this >>= ((A.precision - end) + start);
}

using int16 = Integer<16>;
using int32 = Integer<32>;
using int128 = Integer<128>;
using int256 = Integer<256>;


#endif /* LONG_NUMBERS_H_ */
