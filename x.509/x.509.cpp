#include <x.509.hpp>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* RFC 5754 */
struct rfc5754_ID rfc5754_IDs[] = {
		{
				"sha224WithRSAEncryption",
				{ 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0e,
                        0x05, 00 },
                11
		},
		{
				"sha256WithRSAEncryption",
				{ 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b,
                        0x05, 00 },
                11
		},
		{
				"rsaEncryption",
				{ 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01 },
                9
		}
};

int get_rfc5754_ID(const char *algo)
{
	int i;
	if (algo == NULL)
		return -1;
	for (i = 0; i < sizeof(rfc5754_IDs)/sizeof(*rfc5754_IDs); i++) {
		if (!strcmp(algo, rfc5754_IDs[i].name))
			return i;
	}

	return -2;
}

int x_509_issue_serial_number(struct X_509_certificate& cert)
{
	char __test[9] = "Abcdefgh";
	cert.serial_number[0] = 0;
	memcpy(&cert.serial_number[1], __test, 8);
	return 0;
}

int x_509_set_cert_signature_alg(struct X_509_certificate& cert, const char *algo)
{
	strcpy(cert.cert_signature_alg, algo);
	return 0;
}

int x_509_set_issuer(struct X_509_certificate& cert, struct X_509_unit& issuer)
{
	memcpy(&cert.issuer, &issuer, sizeof(struct X_509_unit));
}

int x_509_set_subject(struct X_509_certificate& cert, struct X_509_unit& subject)
{
	memcpy(&cert.subject, &subject, sizeof(struct X_509_unit));
}

int x_509_set_timestamp(struct X_509_certificate& cert, uint16_t days)
{
	return 0;
}

int x_509_sign_certificate(struct X_509_certificate& cert)
{
	return 0;
}

int x_509_generate_DER()
{
	return 0;
}
