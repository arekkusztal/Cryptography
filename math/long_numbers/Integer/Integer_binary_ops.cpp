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
 * ********** Bit shift operators  **********
*/

template <uint16_t len>
Integer<len> Integer<len>::operator<<(uint16_t shift)
{
   Integer<len> ret;
   int i;
   uint16_t add_len, org_shift;

   shift &= (len - 1);
   org_shift = shift;
   add_len = 0;

   for (i = 0; i < (shift & 0x7); i++) {
        if ( (this->__data[this->__len - 1] >> (7 - i)) & 1)
            add_len = 1;
   }

   i = 0;
   for (i = len - 1; i >= (shift >> 3); i--) {
      ret.__data[i] = this->__data[i - (shift >> 3)];
   }
   for (i = (shift >> 3) - 1; i >= 0; i--) {
      ret.__data[i] = 0;
   }
   i = 0;
   shift &= 0x7;
   if (shift && shift < 8) {

      uint8_t __prev_left = this->__data[i] >> (8 - shift);
      ret.__data[i] <<= shift;
      uint8_t __curr;

      while (i < this->__len + (org_shift >> 3)) {
         i++;
         __curr = this->__data[i];
         ret.__data[i] = ret.__data[i] << shift | __prev_left;
         __prev_left = __curr >> (8 - shift);
      }
   }

   ret.__len = (this->__len + ((org_shift >> 3) + add_len)) > (this->precision >> 3) ?
               (this->precision >> 3) : (this->__len + ((org_shift >> 3) + add_len));
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
Integer<len> Integer<len>::operator>>(uint16_t shift)
{
   Integer<len> ret;
   int i;
   uint16_t sub_len, org_shift;

   shift &= (len - 1);
   org_shift = shift;
   sub_len = 1;

   if (shift >= this->__len_in_bits) {
      /* TODO: Check if to clear as empty ret */
       memset(ret.__data, 0, ret.precision >> 3);
       ret.__len = 0;
       ret.__len_in_bits = 0;
       return ret;
   }

   for (i = 0; i < 8 - (shift & 0x7); i++) {
        if ( (this->__data[this->__len - 1] >> (7 - i)) & 1)
            sub_len = 0;
   }

   i = 0;
   for (i = 0; i < len - (shift >> 3); i++) {
      ret.__data[i] = this->__data[i + (shift >> 3)];
   }
   for (i = (len - 1) - (shift >> 3); i < 16; i++) {
      ret.__data[i] = 0;
   }
   i = this->__len - 1;
   shift &= 0x7;
   if (shift < 8) {
      uint8_t __prev_right = this->__data[i];
      ret.__data[i] >>= shift;
      uint8_t __curr;

      while (i >= 0) {
         i--;
         __curr = this->__data[i];
         ret.__data[i] = this->__data[i] >> shift | (__prev_right << (8 - shift));
         __prev_right = __curr;
      }
   }

   ret.__len = this->__len - (org_shift >> 3) + sub_len;
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
