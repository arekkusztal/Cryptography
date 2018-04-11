#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <long_numbers.hpp>
#include <iostream>

#include <CRYPTO_LIB_common.h>
#include <Arus_dev_kit.h>


uint16_t karatsuba_treshold = 240;

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
   memset(this->__data, 0, this->precision >> 3);
   memcpy(this->__data, A.__data, A.__len + 1);
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


void __padd128(uint8_t *a, uint8_t *b)
{
    asm volatile(
          "movdqu %[in], %%xmm15;"
          "aesenclast %%xmm10, %%xmm15;"
          "movdqu %%xmm15, %[out]"
           : [out] "=m" (a)
           : [in] "m" (b)
    );
}

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> operator+(Integer<len_A> A, Integer<len_B> B)
{
   Integer<len_A> ret;
   uint16_t i, __max_of_two, __complement;
   uint8_t carry;

   carry = 0;
   i = 0;
   __max_of_two = A.__len >= B.__len ?
         A.__len : B.__len;

 /*  if (__builtin_expect(len_A < len_B, 0))
      throw;
   if (__builtin_expect(len_A > len_B, 0)) {
      __complement = __max_of_two;
      __max_of_two = len_B >> 3;
   } */

   uint64_t *__data_ret = (uint64_t *)ret.__data;

   while (i < __max_of_two) {
       uint64_t *__r, *__a, *__b;
       __r = (uint64_t *)&ret.__data[i];
       __a = (uint64_t *)&A.__data[i];
       __b = (uint64_t *)&B.__data[i];

       *__r = *__a + *__b + carry;
       if (__builtin_expect((*__a && *__b), 0)) {
          if (*__r < *__a)
             carry = 1;
          else
             carry = 0;
       } else if ((*__a == UINT64_MAX || *__b == UINT64_MAX) && carry)
          carry = 1;
       else
          carry = 0;
       i += sizeof(*__r);
   }

   /*while (i < __max_of_two)
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
   }*/

 /*  while (i < __complement)
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
   } */

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
        //if (!A.__data[i])
          //  continue;
    	uint8_t __temp = A.__data[i];
        A.__data[i] -= borrow;
        if (__temp < B.__data[i]) {
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
    ret.__len = A.__len;
    ret.__set_len_in_bits();
    return ret;
}
#define DEBUG_MW

int MW_COUNT;

template <uint16_t len_A, uint16_t len_B>
DIV_RESULT<len_A> metoda_wielkanocna(Integer<len_A> A, Integer<len_B> B)
{
	int __local_count;
	//printf("\n metoda_wielkanocna ----------");
	__local_count = MW_COUNT++;
	int i;
    DIV_RESULT<len_A> res = { };

    Integer<len_A> __sub_1 = "1";
    Integer<len_B> __temp;
    DIV_RESULT<len_A> __temp_res[32] = { };
    uint16_t __len_to_shift, __bits_to_shift[32];
    if (A < B) {
        res.ret = "0";
        res.mod = A;

       // res.ret.print_s("ret =F");
       // res.mod.print_s("mod =F");
        return res;
    } else if (A == B) {
    	res.ret = "1";
		res.mod = "0";
		return res;
    } else if (A.__len_in_bits == B.__len_in_bits) {
    	res.ret = "1";
    	res.mod = A - B;
    	return res;
    }

    int __iteration__ = 0, __bits_added = 0, __mod_ladder_cout = 0;
    while (A > B) {
        __temp = B;
        __len_to_shift = A.__len_in_bits - __temp.__len_in_bits;
        __temp <<= __len_to_shift;

        if (A > __temp) {
        	A = A - __temp;
        }
        else if (A < __temp) {
            uint16_t __pos = A.__len_in_bits - 1;
            Integer<len_A> __temp_internal;
            while (A < __temp) {
                if ( (!(A.__data[__pos >> 3] >> (__pos & 0x7) & 1))
                     && (__temp.__data[__pos >> 3] >> (__pos & 0x7) & 1))
                {
                    A |= __pos;
                    __temp_internal |= __pos;
                }
                __pos--;

            }
            __temp_res[__mod_ladder_cout] = metoda_wielkanocna(__temp_internal, B);
            __temp_internal = __temp_internal >> 128;
            __mod_ladder_cout++;
            A = A - __temp;
        } else if (A == __temp) {
        	A = "0";
        }


        res.ret |= __len_to_shift;

    }

    for (i = 0; i < __mod_ladder_cout; i++) {
      if (A < __temp_res[i].mod) {
    	    A = A + B;
    		res.ret = res.ret - __sub_1;
    	}
		A = A - __temp_res[i].mod;
		res.ret = res.ret - __temp_res[i].ret;
    }

    res.mod = A;
   // res.ret.print_s("ret =");
   // res.mod.print_s("mod =");



    return res;
}

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> operator/(Integer<len_A> A, Integer<len_B> B)
{
   DIV_RESULT<len_A> res;
   res = metoda_wielkanocna(A, B);

   return res.ret;
}

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> operator*(const Integer<len_A> &&A, const Integer<len_B>& B)
{
    return A * B;
}

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> operator*(const Integer<len_A> &A, const Integer<len_B>& B)
{
   Integer<len_A> ret;

   if (A.__len > karatsuba_treshold && B.__len > karatsuba_treshold) {
   //    printf("\nINFO: Entering Karatsuba A.len >> 1 = %hu", A.__len >> 1);
       return karatsuba(A, B);
   }

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

#define __DEBUG_

#ifdef __DEBUG
#define DEBUG_PRINTF(str) printf(str);
#define DEBUG_PRINT(arg,str) arg.print_s(str);
#else
#define DEBUG_PRINTF(str)
#define DEBUG_PRINT(arg,str)
#endif

#define KARATSUBA_BYTE_OFFSET 120
template <uint16_t len_A, uint16_t len_B>
Integer<len_A> karatsuba(const Integer<len_A>& A, const Integer<len_B>& B)
{
    Integer<len_A> ret;
    if (A.__len_in_bits + B.__len_in_bits > A.precision) {
        printf("\nINFO: potential overflow = %hu", A.__len_in_bits + B.__len_in_bits);
        return ret;
    }

    uint16_t __chosen_one, __b;

    Integer<len_A> Z_0, Z_1, Z_2;
    Integer<len_A> x_0, x_1, y_0, y_1;

    if (KARATSUBA_BYTE_OFFSET >= (A.__len)) {
     //   printf("\nINFO: Leaving Karatsuba A.__len/2 = %hu", A.__len >> 1);
        return A * B;
    }
    /* TODO: test it */
    /* __chosen_one = A.__len_in_bits - 1; */
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
    ret = (Z_2 << __b) + (Z_1 << __chosen_one) + Z_0;

    return ret;
}

/*
 * ********** Bit shift operators  **********
*/

template <uint16_t len>
Integer<len> operator<<(const Integer<len>& A, uint16_t shift)
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
         ret.__data[i] = ret.__data[i] << shift | __prev_left;
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

   org_shift = shift;
   add_len = 0;

   for (i = 0; i < (shift & 0x7); i++) {
        if ( (this->__data[this->__len - 1] >> (7 - i)) & 1)
            add_len = 1;
   }

   i = 0;
   for (i = (len >> 3) - 1; i >= (shift >> 3); i--) {
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
Integer<len> operator>>(const Integer<len>& A, uint16_t shift)
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
   for (i = 0; i < (len >> 3) - (shift >> 3); i++) {
      this->__data[i] = this->__data[i + (shift >> 3)];
   }

   for (i = (len >> 3) - (shift >> 3); i < this->__len; i++) {
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
 * ********** Logical operators  **********
*/

template <uint16_t len_A, uint16_t len_B>
bool operator>(Integer<len_A> A, Integer<len_B> B)
{
    int i;
    if (A.__len_in_bits > B.__len_in_bits)
        return true;
    else if (A.__len_in_bits < B.__len_in_bits)
        return false;
    else {
        i = A.__len;
        while (i >= 0) {
            if (A.__data[i] > B.__data[i])
                return true;            
            else if (A.__data[i] < B.__data[i])
                return false;
            i--;
        }

    }
    return false;
}

template <uint16_t len_A, uint16_t len_B>
bool operator<(Integer<len_A> A, Integer<len_B> B)
{
    int i;
    if (A.__len_in_bits < B.__len_in_bits)
        return true;
    else if (A.__len_in_bits > B.__len_in_bits)
        return false;
    else {
        i = A.__len - 1;
        while (i >= 0) {
            if (A.__data[i] < B.__data[i])
                return true;
            else if (A.__data[i] > B.__data[i])
                return false;
            i--;
        }

    }
    return false;
}

template <uint16_t len>
bool Integer<len>::operator==(Integer<len> A)
{
	int i;
	if (this->__len_in_bits != A.__len_in_bits)
		return false;

	if (!memcmp(this->__data, A.__data, this->__len))
		return true;
	else
		return false;
}


template <uint16_t len>
Integer<len>& Integer<len>::operator&(Integer<len>&)
{

    return *this;
}

template <uint16_t len>
Integer<len>& Integer<len>::operator|=(BNLib_int_size pos)
{
    BNLib_int_size __byte_to_change;
    if (pos >= this->precision)
        return *this;

    __byte_to_change = pos >> 3;
    pos &= 0x7;
    this->__data[__byte_to_change] |= (1 << pos);
    if (__byte_to_change > this->__len - 1)
        this->__len = __byte_to_change + 1;

    this->__set_len_in_bits();
    return *this;
}

/*
 * ********** Misc member functions  **********
*/

template <uint16_t len>
void Integer<len>::__set_len_in_bits()
{
    int i;
  //  while (1) {
    if (this->__len == 0) {
      this->__len_in_bits = 0;
      this->__data[0] = 0;
      return;
    }

    for (i = 7; i >= 0; i--) {
        if ((this->__data[this->__len - 1] >> i) & 1) {
            this->__len_in_bits = ((this->__len - 1) << 3) + i + 1;
            return;
        }
    }
    //this->__len_in_bits = ((this->__len - 1) << 3) + i + 1;
    this->__data[this->__len - 1] = 0;
    this->__len -= 1;
   // }
    this->__set_len_in_bits();
}

template <uint16_t len_A, uint16_t len_B>
Integer<len_A> integer_cast(Integer<len_B> B)
{
   Integer<len_A> ret;

   return ret;
}

template <uint16_t len>
void Integer<len>::print(const char * str)
{
   hex_dump(str, this->__data, this->__len, 16);
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



template class Integer<16>;
template Integer<16> operator*(const Integer<16>&& A, const Integer<16>& B);
template Integer<16> operator*(const Integer<16>& A, const Integer<16>& B);
template Integer<16> karatsuba(const Integer<16>& A, const Integer<16>& B);

template class Integer<32>;
template Integer<32> operator*(const Integer<32>&& A, const Integer<32>& B);
template Integer<32> operator*(const Integer<32>& A, const Integer<32>& B);
template Integer<32> karatsuba(const Integer<32>& A, const Integer<32>& B);

template class Integer<128>;
template Integer<128> operator*(const Integer<128>&& A, const Integer<128>& B);
template Integer<128> operator*(const Integer<128>& A, const Integer<128>& B);
template Integer<128> karatsuba(const Integer<128>& A, const Integer<128>& B);
template bool operator>(const Integer<128> A, const Integer<128> B);
template bool operator<(const Integer<128> A, const Integer<128> B);
template DIV_RESULT<128> metoda_wielkanocna(Integer<128> A, Integer<128> B);
template Integer<128> operator/(Integer<128> A, Integer<128> B);

template Integer<128> operator+(Integer<128> A, Integer<128> B);
template Integer<128> operator-(Integer<128> A, Integer<128> B);

template class Integer<256>;
template Integer<256> operator*(const Integer<256>&& A, const Integer<256>& B);
template Integer<256> operator*(const Integer<256>& A, const Integer<256>& B);
template Integer<256> karatsuba(const Integer<256>& A, const Integer<256>& B);

template class Integer<512>;
template Integer<512> operator*(const Integer<512>&& A, const Integer<512>& B);
template Integer<512> operator*(const Integer<512>& A, const Integer<512>& B);
template Integer<512> karatsuba(const Integer<512>& A, const Integer<512>& B);

template class Integer<4096>;
template Integer<4096> operator*(const Integer<4096>&& A, const Integer<4096>& B);
template Integer<4096> operator*(const Integer<4096>& A, const Integer<4096>& B);
template Integer<4096> karatsuba(const Integer<4096>& A, const Integer<4096>& B);

template class Integer<8192>;
template Integer<8192> operator*(const Integer<8192>&& A, const Integer<8192>& B);
template Integer<8192> operator*(const Integer<8192>& A, const Integer<8192>& B);
template Integer<8192> karatsuba(const Integer<8192>& A, const Integer<8192>& B);
