#include <ASN.1.hpp>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void rev_memcpy(uint8_t *to, uint8_t *from, uint16_t len)
{

}

uint8_t *ASN_1_set(uint8_t *where, struct ASN_1_ID_octet octet, uint8_t *string, uint16_t len)
{
	uint8_t __size = 2;

	*where |= (ASN_1_SET_TAG(octet.tag));
	*where |= (ASN_1_SET_PC(octet.pc));
	*where |= octet.type;

	if (len > ASN_1_SHORT_MAX) {
		len -= 4;

		where++;
		*where |= ASN_1_DEF_LONG;
		*where |= __size;
		where++;
		//memcpy(where, (uint8_t *)&len, __size);

	} else {
		len -= 2;
		where++;
		*where |= len;
	}
	return where;
}
