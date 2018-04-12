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

template<uint16_t len>
template<uint16_t __len>
Integer<__len> Integer<len>::integer_cast(Integer<len>)
{
	Integer<len> ret;
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
