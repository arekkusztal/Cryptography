#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <long_numbers.hpp>

#include <Arus_dev_kit.h>
#include <iostream>

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

}
