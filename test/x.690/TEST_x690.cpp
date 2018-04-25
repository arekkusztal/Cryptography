
#include <stdint.h>
#include <ASN.1.hpp>
#include <Arus_dev_kit.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CERT_SIZE 0x503
#define SIZE_BEFORE_SIGN	0x503 - 513 - 8

int main()
{
	uint8_t cert[CERT_SIZE] = { };
	uint8_t *curr_ptr = cert;
	struct ASN_1_ID_octet id_octet = { UNIVERSAL, CONSTRUCTED, SEQUENCE };
	curr_ptr = ASN_1_set(curr_ptr, id_octet, (uint8_t *)NULL, CERT_SIZE);
	curr_ptr = ASN_1_set(curr_ptr, id_octet, (uint8_t *)NULL, SIZE_BEFORE_SIGN);
	id_octet.type = EOC;
	id_octet.tag = CONTEXT_SPECIFIC;
	curr_ptr = ASN_1_set(curr_ptr, id_octet, (uint8_t *)NULL, 3);

	hex_dump("cert", cert, 64, 16);
	return 0;
}
