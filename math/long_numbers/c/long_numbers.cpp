#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <long_numbers.hpp>

#include <Arus_dev_kit.h>

/*
int
set_integer_128_b16(uint8_t *array, struct Integer *A, int len) {
	int i, k;
	if (len == 0)
		len = 128;
	else if (len >128 || len < 0) {
		perror("");
		return -1;
	}

	for (i = len-1, k =0; i>=0; i--, k+=2) {
		A->data[i] += HEX_ME(array[k]) * 16;
		A->data[i] += HEX_ME(array[k + 1]);
	}
	hex_dump("Long number (set_integer b_16)", A->data, len , 32);
	A->size = len;
	return 0;
}
*/

void int128_t::print()
{
	hex_dump("int128", this->__data, this->precision, 16);
}

int128_t::int128_t(const int128_t &T)
{
    memcpy(this, &T, sizeof(*this));
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
}

#define intN_t_add \
		__max_of_two = this->__len >= B.__len ?		\
				this->__len : B.__len;		\
		carry = 0;		\
		i = 0;	\
		while (i < __max_of_two) \
		{ \
			uint8_t t_a = this->__data[i], t_b = B.__data[i];	\
			__b = this->__data[i] + B.__data[i] + carry; \
			this->__data[i] = __b; \
			if (__builtin_expect((t_a && t_b), 1)) { \
				if (__b < t_a || __b < t_b) \
					carry = 1; \
				else \
					carry = 0; \
			} else if ((t_a == 0xFF || t_b == 0xFF) && carry) \
				carry = 1; \
			else \
				carry = 0; \
			i++; \
		}

int128_t int128_t::operator+=(int128_t B)
{
	uint16_t i, k, __max_of_two;
	uint8_t carry, __b;

	intN_t_add;
	/*
	* If carry general overflow
	*/

	return *this;
}

int128_t int128_t::operator*=(int128_t B)
{
   int128_t __temp, __shifted;
   uint16_t i, k, __min_of_two;
   uint8_t __a_is_smaller;

   if (this->__len <= B.__len) {
       __a_is_smaller = true;
   }
   else {
       __shifted = *this;
       __a_is_smaller = false;
   }

   if (__a_is_smaller) {

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
   this->__len = this->__len + B.__len;

   return *this;
}

int128_t int128_t::operator<<=(uint16_t shift)
{
	int i;
	shift &= ~0x80;

	i = 0;

   for (i = 15; i >= (shift >> 3); i--) {
        this->__data[i] = this->__data[i - (shift >> 3)];
   }
   for (i = (shift >> 3) - 1; i >= 0; i--) {
        this->__data[i] = 0;
   }

   shift &= 0x7;


	if (shift < 8) {
		uint8_t __prev_left = this->__data[i] >> (8 - shift);
		this->__data[i] <<= shift;
		uint8_t __curr;

		while (i < this->__len) {
			i++;
			__curr = this->__data[i];
			this->__data[i] = this->__data[i] << shift | __prev_left;
			__prev_left = __curr >> (8 - shift);
		}
		this->__data[0] |= __prev_left;
	}

   this->__len += (shift >> 8) + 1;

	return *this;
}

int128_t int128_t::operator=(int128_t A)
{
    memcpy(this, &A, sizeof(*this));
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
