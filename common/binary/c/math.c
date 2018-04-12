#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <CRYPTO_LIB_common.h>

void ror_4(uint8_t *data, uint16_t bg)
{
	int i;

	uint8_t temp[4];
	for (i = bg; i < bg + 4; i++) {
		temp[i - bg] = data[i & 3];
	}
	memcpy(data, temp, 4);
}

void rol_4(uint8_t *data, uint16_t bg)
{
	int i;

	uint8_t temp[4];
	for (i = bg; i < bg + 4; i++) {
		temp[i - bg] = data[(4 - 2*bg + i) & 3];
	}
	memcpy(data, temp, 4);
}
