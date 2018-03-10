#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


uint16_t LFSR_16(uint16_t arg, uint16_t mask)
{
	uint16_t i, xored = 0;

	for (i = 0; i < 16; i++) {
		if (mask & i)
			xored ^= (arg >> i) & 1;
	}
	arg = arg << 15 | xored >> 1;
	return arg;
}
