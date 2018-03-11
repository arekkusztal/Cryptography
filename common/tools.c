#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <long_numbers.h>

void hex_dump(const char *def, uint8_t *data, uint16_t len,
		uint16_t br)
{
	uint16_t i;

	printf("\n%s:\n", def);
	for (i = 0; i < len; ++i) {
		if (i && ( i % br ==0 ))
			printf("\n");
		printf("0x%02X ",data[i]);
	}
	printf("\n");
}

void bit_dump_b(uint8_t data)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{
		printf("%d", (data >> (7 - i)) & 1);
	}
	printf("\n");
}

void bit_dump_s(uint8_t *data, int size)
{
	uint8_t i;
	int j;

	for (j = size -1; j >= 0; j--)
		for (i = 0; i < 8; i++)
		{
			printf("%d", (data[j] >> (7 - i)) & 1);
		}
	printf("\n");
}

