#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <Arus_dev_kit.h>

#define LFSR_DEBUG

#ifdef LFSR_DEBUG
#define bit_dump_b(arg) bit_dump_b(arg)
#define bit_dump_s(arg, size) bit_dump_b(arg, size)
#else
#define bit_dump_b(arg)
#define bit_dump_s(arg, size)
#endif

uint16_t LFSR_16(uint16_t arg, uint16_t mask)
{
	uint16_t i, xored = 0;

	for (i = 0; i < 16; i++) {
		if ((mask >> i) & 1)
			xored ^= (arg >> i) & 1;
	}
	arg = arg << 15 | xored >> 1;
	return arg;
}

uint8_t LFSR_8(uint8_t arg, uint8_t mask)
{
	uint8_t i, xored = 0, org = arg;
	do {
		for (i = 0; i < 8; i++) {
			if ((mask >> i) & 1)
				xored ^= (arg >> i) & 1;
		}
		arg = xored << 7 | arg >> 1;
		xored = 0;
		bit_dump_b(arg);
	} while (org != arg);
	return arg;
}

uint8_t LFSR_4(uint8_t arg, uint8_t mask)
{
	uint8_t i, xored = 0, org = arg;
	bit_dump_b(arg);
	do {
		for (i = 0; i < 4; i++) {
			if ((mask >> i) & 1)
				xored ^= (arg >> i) & 1;
		}
		arg = xored << 3 | arg >> 1;
		xored = 0;
		bit_dump_b(arg);
	} while (org != arg);
	return arg;
}

#undef bit_dump_b
#undef bit_dump_s
