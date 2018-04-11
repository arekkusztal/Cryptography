#include <long_numbers.hpp>

/*
 * ********** Arithmetic operators  **********
 */
/*
 * @brief Add operator, works when len of A is equal or bigger than len of B
 *
 */

template <uint16_t len>
Integer<len> Integer<len>::operator+(const Integer<len>& B)
{
   Integer<len> ret;
   uint16_t i, __max_of_two, __complement;
   uint8_t carry;

   carry = 0;
   i = 0;
   __max_of_two = this->__len >= B.__len ?
         this->__len : B.__len;

   uint64_t *__data_ret = (uint64_t *)ret.__data;

   while (i < __max_of_two) {
       uint64_t *__r, *__a, *__b;
       __r = (uint64_t *)&ret.__data[i];
       __a = (uint64_t *)&this->__data[i];
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

   ret.__len = __complement ? __complement : __max_of_two;
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

template <uint16_t len>
Integer<len> Integer<len>::operator-(const Integer<len>& B)
{
    Integer<len> ret;
    uint16_t i, k, __max_of_two;
    uint8_t borrow, __b;
    __max_of_two = this->__len >= B.__len ?		\
          this->__len : B.__len;

    borrow = 0;

    for (i = 0; i < this->__len;i++) {
        uint8_t __temp = this->__data[i];
        if (!__temp)
            __temp -= borrow;
        else
            if (B.__data[i]) {
                ret.__data[i] = 0xFF - B.__data[i];
                borrow = 1;
                continue;
            } else
                continue;

        if (__temp < B.__data[i]) {
            borrow = 1;
            uint16_t ext_1 = this->__data[i];
            ext_1 += 0x100;
            ext_1 -= B.__data[i];
            ret.__data[i] = ext_1;
        }
        else {
            ret.__data[i] = this->__data[i] - B.__data[i];
            borrow = 0;
        }
    }
    ret.__len = this->__len;
    ret.__set_len_in_bits();
    return ret;
}

template <uint16_t len>
Integer<len>& Integer<len>::operator+=(const Integer<len>& B)
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

