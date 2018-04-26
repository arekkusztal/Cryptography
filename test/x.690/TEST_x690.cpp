
#include <stdint.h>
#include <Arus_dev_kit.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ASN.1.hpp>
#include <x.509.hpp>


#define CERT_SIZE 0x503
#define SIZE_BEFORE_SIGN	0x503 - 513 - 8

char issuer[] = "Arus";
const char signature_algo[] = "sha224WithRSAEncryption";

void TEST_fill_certificate(struct X_509_certificate& cert)
{
	cert.version = X_509_VERSION_3;
	x_509_issue_serial_number(cert);
	x_509_set_cert_signature_alg(cert, "sha224WithRSAEncryption");
	struct X_509_unit issuer;
	strcpy(issuer.company_name, "Company Name");
	memcpy(issuer.country, "PL", 2);
	strcpy(issuer.location, "Lodz");
	strcpy(issuer.organization, "Company Name");
	strcpy(issuer.organization_unit, "Security Lab");
	strcpy(issuer.state, "Lodzkie");
	struct X_509_unit subject;
	x_509_set_issuer(cert, issuer);

}

int main()
{
	struct X_509_certificate TEST_certificate_1 = { };
	TEST_fill_certificate(TEST_certificate_1);
/*	uint8_t cert[CERT_SIZE] = { };
	uint8_t *curr_ptr = cert;
	struct ASN_1_ID_octet id_octet = { UNIVERSAL, CONSTRUCTED, SEQUENCE };
	curr_ptr = ASN_1_set(curr_ptr, id_octet, (uint8_t *)NULL, CERT_SIZE);
	curr_ptr = ASN_1_set(curr_ptr, id_octet, (uint8_t *)NULL, SIZE_BEFORE_SIGN);
	id_octet.type = EOC;
	id_octet.tag = CONTEXT_SPECIFIC;

	hex_dump("cert", cert, 64, 16); */
	return 0;
}
