#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <CRYPTO_LIB_common.h>

void ror_4(uint8_t *data, uint16_t bg)
{
	bg <<= 3;
	asm volatile (
			"movb %[__bg], %%cl\n"
			"rorl %%cl, %[__data]\n"
			:
			: [__data] "m" (*(uint32_t *)data), [__bg] "m" (bg)
	);
}

void rol_4(uint8_t *data, uint16_t bg)
{
	bg <<= 3;
	asm volatile (
			"movb %[__bg], %%cl\n"
			"roll %%cl, %[__data]\n"
			:
			: [__data] "m" (*(uint32_t *)data), [__bg] "m" (bg)
	);
}
