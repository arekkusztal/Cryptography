#include <x.509.hpp>
#include <stdlib.h>
#include <string.h>

/* RFC 5754 */
struct rfc5754_ID rfc5754_IDs[] = {
		{
				"sha224WithRSAEncryption",
				{ 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0e,
                        0x05, 00 },
                9
		}
};

int x_509_issue_serial_number(struct X_509_certificate& cert)
{
	char __test[9] = "Abcdefgh";
	memcpy(&cert.serial_number[1], __test, 8);
	return 0;
}

int x_509_set_cert_signature_alg(struct X_509_certificate& cert, const char *algo);

int x_509_generate_DER()
{
	return 0;
}
