
#include <stdint.h>
#include <ASN.1.hpp>
#include <Arus_dev_kit.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CERT_SIZE 0x503

int main()
{
	uint8_t cert[CERT_SIZE] = { };
	uint8_t *curr_ptr = cert;
	struct ASN_1_ID_octet id_octet = { UNIVERSAL, CONSTRUCTED, SEQUENCE };
	ASN_1_set(curr_ptr, id_octet, (uint8_t *)NULL, CERT_SIZE);

	hex_dump("cert", cert, 64, 16);
	return 0;
}
