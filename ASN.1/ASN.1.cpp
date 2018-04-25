#include <ASN.1.hpp>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void rev_memcpy(uint8_t *to, uint8_t *from, uint16_t len)
{
	uint16_t i;
	for (i = 0; i < len; i++)
		to[i] = from[len - 1 - i];
}

uint8_t *ASN_1_set(uint8_t *where, struct ASN_1_ID_octet octet, uint8_t *string, uint16_t len)
{
	uint8_t __num_of_octets = 2;

	*where |= (ASN_1_SET_TAG(octet.tag));
	*where |= (ASN_1_SET_PC(octet.pc));
	*where |= octet.type;

	if (len > ASN_1_SHORT_MAX) {
		where++;
		*where |= ASN_1_DEF_LONG;
		*where |= __num_of_octets;
		where++;
		rev_memcpy(where, (uint8_t *)&len, __num_of_octets);
		where += __num_of_octets;

	} else {
		where++;
		*where |= len;
	}
	return where;
}
