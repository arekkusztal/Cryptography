#include <Integer.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include <CRYPTO_LIB_common.h>
#include <Arus_dev_kit.h>

/*
 * ********** Arithmetic operators  **********
 */
/*
 * @brief Add operator
 *
 */

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign> Integer<len, sign>::operator+(const Integer<len, sign>& B)
{
   Integer<len, sign> ret;
   uint16_t i, __max_of_two, __complement;
   uint8_t carry;

   carry = 0;
   i = 0;
   __max_of_two = this->__len >= B.__len ?
         this->__len : B.__len;

   while (i < __max_of_two) {
       uint8_t *__r, *__a, *__b;
       __r = (uint8_t *)&ret.__data[i];
       __a = (uint8_t *)&this->__data[i];
       __b = (uint8_t *)&B.__data[i];

       *__r = *__a + *__b + carry;
       if (likely(*__a && *__b)) {
          if (*__r < *__a  || *__r < *__b)
             carry = 1;
          else
             carry = 0;
       } else if ((*__a == UINT8_MAX || *__b == UINT8_MAX) && carry)
          carry = 1;
       else
          carry = 0;
       i += sizeof(*__r);
   }

   ret.__len = __max_of_two;
   if (carry) {
      ret.__data[i] = 1;
      ret.__len += 1;
      if (ret.__len > (len >> 3)) {
         ret.__len -= (len >> 3);
      }
   }
   ret.__set_len_in_bits();

   return ret;
}

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign> Integer<len, sign>::operator-(const Integer<len, sign>& B)
{
    Integer<len, sign> ret;
    uint16_t i, k, __max_of_two, __true_len;
    uint8_t borrow, __b;
    __max_of_two = this->__len >= B.__len ?
          this->__len : B.__len;

    if (*this < B) {
    	__true_len = len >> 3;
    } else
    	__true_len = this->__len;

    borrow = 0;

    for (i = 0; i < __true_len; i++) {
        uint8_t __temp = this->__data[i];
        if (!__temp) {
            if (B.__data[i]) {
                ret.__data[i] = __temp - B.__data[i];
                borrow = 1;
            } else {
            	if (borrow)
            		ret.__data[i] = 0xFF;
            }
        } else {
        	if (__temp < B.__data[i] || (__temp == B.__data[i] && borrow)) {
				borrow = 1;
				uint16_t ext_1 = this->__data[i];
				ext_1 += 0x100;
				ext_1 -= B.__data[i];
				ret.__data[i] = ext_1;
			}
			else {
				ret.__data[i] = this->__data[i] - B.__data[i] - borrow;
				borrow = 0;
			}
        }
    }

    ret.__len = __true_len;
    ret.__set_len_in_bits();
    return ret;
}

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign>& Integer<len, sign>::operator++()
{
	uint64_t __carry = 1;
	uint16_t __pos = 0;
	while (__carry) {
		*(uint64_t *)&this->__data[__pos] += __carry;
		if (!(*(uint64_t *)&this->__data[__pos])) {
			__carry = 1;
			__pos += sizeof(uint64_t);
		} else
			__carry = 0;
	};
	return *this;
}

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign>& Integer<len, sign>::operator++(int)
{
	uint64_t __carry = 1;
	uint16_t __pos = 0;
	while (__carry) {
		*(uint64_t *)&this->__data[__pos] += __carry;
		if (!(*(uint64_t *)&this->__data[__pos])) {
			__carry = 1;
			__pos += sizeof(uint64_t);
		} else
			__carry = 0;
	};
	return *this;
}

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign>& Integer<len, sign>::operator+=(const Integer<len, sign>& B)
{
   uint16_t i, __max_of_two;
   uint8_t carry;

   carry = 0;
   i = 0;
   __max_of_two = this->__len >= B.__len ?
         this->__len : B.__len;

   while (i < __max_of_two)
   {
      uint8_t __tmp_A = this->__data[i];
      this->__data[i] = this->__data[i] + B.__data[i] + carry;
      if (__builtin_expect((this->__data[i] && B.__data[i]), 1)) {
         if (this->__data[i] < __tmp_A || this->__data[i] < B.__data[i])
            carry = 1;
         else
            carry = 0;
      } else if ((__tmp_A == 0xFF || B.__data[i] == 0xFF) && carry)
         carry = 1;
      else
         carry = 0;
      i++;
   }

   this->__len = __max_of_two;
   if (carry) {
      this->__data[i] = 1;
      this->__len += 1;
      if (this->__len > (len >> 3)) {
         this->__len -= (len >> 3);
      }
   }
   this->__set_len_in_bits();

   return *this;
}

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign> Integer<len, sign>::operator*(const Integer<len, sign>& B)
{
   Integer<len, sign> ret;

   if (this->__len > karatsuba_treshold && B.__len > karatsuba_treshold) {
   //    printf("\nINFO: Entering Karatsuba A.len >> 1 = %hu", A.__len >> 1);
       return this->karatsuba(B);
   }

   Integer<len, sign> __temp, __shifted;
   uint16_t i, k, __min_of_two, __final_len;
   uint8_t __a_is_smaller;

   __temp.__len = 1;
   __temp.__len_in_bits = 8;
   __final_len = ((this->__len_in_bits + B.__len_in_bits - 1) >> 3) + 1;


   if (this->__len <= B.__len) {
       __shifted = B;
       __a_is_smaller = true;
   }
   else {
       __shifted = *this;
       __a_is_smaller = false;
   }

   if (__a_is_smaller) {
       for (i = 0; i < this->__len << 3; i++) {
           if ( (this->__data[i >> 3] >> (i & 0x7)) & 1) {
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

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign> Integer<len, sign>::operator/(const Integer<len, sign> &B)
{
   DIV_RESULT<len, sign> res;
   res = this->metoda_wielkanocna(B);

   return res.ret;
}

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign> Integer<len, sign>::operator%(const Integer<len, sign> &B)
{
   DIV_RESULT<len, sign> res;
   res = this->metoda_wielkanocna(B);

   return res.mod;
}

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign> Integer<len, sign>::mod_exp(const Integer<len, sign>& exp, const Integer<len, sign>& mod)
{
	uint16_t i;
	Integer<len, sign> res, first;

	first = *this % mod;

	if (exp.__data[0] & 1) {
		res = first;
	}

	for (i = 1; i < exp.__len_in_bits; i++) {
		first.print_s("first");
		first = ((first % mod) * (first % mod)) % mod;
		if ((exp.__data[i >> 3] >> (i & 0x7)) & 1) {
			res = res * first;
		}
	}

	res = res % mod;

	return res;
}


template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign> Integer<len, sign>::mod_inv(const Integer<len, sign>& exp, const Integer<len, sign>& mod)
{
	Integer<len, sign> __a, q, __temp_mod, __mod;
	Integer<len, sign> y = "0", x = "1";
	Integer<len, sign> __one = "1";
	Integer<len, sign> __zero = "1";

	__mod = mod;
	__a = exp;

	if (__mod == x)
		return y;

	while (__a > __one)
	{
		q = __a / __mod;
		__temp_mod = __mod;

		__mod = __a % __mod;
		__a = __temp_mod;
		__temp_mod = y;

		y = x - q * y;
		x = __temp_mod;
	}

	if (x < __zero)
		x += mod;

	return x;
}

