#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <long_numbers.hpp>

#include <CRYPTO_LIB_common.h>
#include <Arus_dev_kit.h>


void int128_t::print()
{
   hex_dump("int128", this->__data, this->__len, 16);
}

void int128_t::print_s(const char * str)
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

int128_t::int128_t(const int128_t &T)
{
    memcpy(this, &T, sizeof(*this));
}

int128_t::int128_t(int128_t, uint16_t start, uint16_t end)
{

}

inline void int128_t::__set_len_in_bits()
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

int128_t::int128_t(const char *number)
{
	uint16_t __len, i, prefix;

	__len = strlen(number);
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

int128_t::int128_t(unsigned char *number)
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
int128_t int128_t::operator+=(int128_t B)
{
	uint16_t i, k, __max_of_two;
   uint8_t carry, __b;

	__max_of_two = this->__len >= B.__len ?
			this->__len : B.__len;
	carry = 0;
	i = 0;
	while (i < __max_of_two)
	{
		uint8_t t_a = this->__data[i], t_b = B.__data[i];
		__b = this->__data[i] + B.__data[i] + carry;
		this->__data[i] = __b;
		if (__builtin_expect((t_a && t_b), 1)) {
			if (__b < t_a || __b < t_b)
				carry = 1;
			else
				carry = 0;
		} else if ((t_a == 0xFF || t_b == 0xFF) && carry)
			carry = 1;
		else
			carry = 0;
		i++;
	}
	if (carry) {
		this->__data[i] = 1;
		this->__len += 1;
	}
	/*
	* If carry general overflow
	*/

	return *this;
}

int128_t& int128_t::operator-=(int128_t B)
{
    uint16_t i, k, __max_of_two;
    uint8_t borrow, __b;

    __max_of_two = this->__len >= B.__len ?		\
          this->__len : B.__len;

    borrow = 0;

    for (i = 0; i < this->__len;i++) {
        if (!this->__data[i])
            continue;

        this->__data[i] -= borrow;
        if (this->__data[i] < B.__data[i]) {
            borrow = 1;
            uint16_t ext_1 = this->__data[i];
            ext_1 += 0x100;
            ext_1 -= B.__data[i];
            this->__data[i] = ext_1;
        }
        else {
            this->__data[i] -= B.__data[i];
            borrow = 0;
        }
    }

    return *this;
}

int128_t& int128_t::operator*=(int128_t B)
{
   int128_t __temp, __shifted;
   uint16_t i, k, __min_of_two, __final_len;
   uint8_t __a_is_smaller;

   __temp.__len = 1;
   __temp.__len_in_bits = 8;
   __final_len = this->__len + B.__len;


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

   *this = __temp;
   this->__len = __final_len;
   __set_len_in_bits();

   return *this;
}

int128_t int128_t::operator<<=(uint16_t shift)
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
}

int128_t int128_t::operator>>=(uint16_t shift)
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


int int128_t::copy_bits(int128_t A, uint16_t start, uint16_t end)
{
	*this = A;
	*this <<= (128 - end);
	*this >>= ((128 - end) + start);
}

int128_t int128_t::karatsuba(int128_t B)
{
#define OFFSET_CONSTANT 1
    int i, k;
    uint16_t __b;
    uint8_t __likely_overflow;
    uint16_t __chosen_one;
    int128_t Z_0, Z_1, Z_2;
    int128_t x_0, x_1, y_0, y_1;

/*    if (this->__len_in_bits <= 64 || B.__len_in_bits <= 64) {
        this->error_code = too_small_to_bother;
        return *this;
    }

    if (this->__len_in_bits + B.__len_in_bits >= this->precision) {
        this->error_code = potential_overflow;
        return *this;
    }*/

    /* Choose it wisely for both args */
    __chosen_one = this->__len_in_bits - OFFSET_CONSTANT;
    __chosen_one += !(__chosen_one & 1);
  //  __b = ( ((__chosen_one - 1) >> 1) + 1);
    __b = (__chosen_one << 1) - 1;
    x_0.copy_bits(*this, __chosen_one - 1, this->__len_in_bits);
    x_0.print_s("x_0");
    x_1.copy_bits(B, __chosen_one - 1, __len_in_bits);
    x_0.print_s("x_1");

    y_0.copy_bits(*this, 0, __chosen_one - 2);
    y_0.print_s("y_0");

    y_1.copy_bits(B, 0, __chosen_one - 2);
    y_1.print_s("y_1");
    Z_2 = x_0;
    Z_2 *= x_1;
    Z_2.print_s("Z_2");

    printf("\n == Z_0");
    Z_0 = y_0;
    Z_0.print();
    Z_0 *= y_1;
    Z_0.print_s("Z_0");
    Z_0.print();
    Z_0.print_s("Z_0");

    Z_1 = x_0;

    Z_1 += y_0;
    Z_1.print();

    Z_1 += y_1;
    Z_1.print();

    Z_1 *= x_1;
    Z_1.print();

    Z_1 -= Z_2;
    Z_1.print();

    x_0 -= Z_0;
    Z_1.print();

    Z_2 <<= __b - 1;
    Z_2.print();
    Z_1 <<= __chosen_one - 1;
    Z_1.print();
    Z_0.print();

    Z_2 += Z_1;
    Z_2 += Z_0;
    Z_2.print();

}

int128_t int128_t::operator=(int128_t A)
{
    memcpy(this, &A, sizeof(*this));
}

bool int128_t::operator==(int128_t *A)
{
    if (this->__len_in_bits != A->__len_in_bits)
        return false;
    return !memcmp(this->__data, A->__data, this->__len);
}

bool int128_t::operator==(unsigned char *s)
{
    return !memcmp(this->__data, s, this->__len);
}


/*
	__max_of_two = this->__len >= B.__len ?
			this->__len : B.__len;
	carry = 0;
	i = 0;

	while (i < __max_of_two)
	{
		uint8_t t_a = this->__data[i], t_b = B.__data[i];
		__b = this->__data[i] + B.__data[i] + carry;
		this->__data[i] = __b;

		if (__builtin_expect((t_a && t_b), 1)) {
			if (__b < t_a || __b < t_b)
				carry = 1;
			else
				carry = 0;
		} else if ((t_a == 0xFF || t_b == 0xFF) && carry)
			carry = 1;
		else
			carry = 0;
		i++;
	} */
