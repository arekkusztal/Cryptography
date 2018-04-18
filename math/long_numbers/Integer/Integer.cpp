#include <Integer.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include <CRYPTO_LIB_common.h>
#include <Arus_dev_kit.h>


uint16_t karatsuba_treshold = 240;

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign>::Integer(uint8_t *number)
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

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign>::Integer(const char *number)
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

template <uint16_t len, SIGNEDNESS sign>
Integer<len, sign> Integer<len, sign>::operator=(Integer<len, sign> A)
{
   memset(this->__data, 0, this->precision >> 3);
   memcpy(this->__data, A.__data, A.__len + 1);
   this->__len = A.__len;
   this->__len_in_bits = A.__len_in_bits;
}


