#ifndef X_509_H
#define X_509_H

#include <stdint.h>

/* RFC 5754 */
struct rfc5754_ID
{
	const char name[32];
	const uint8_t id[16];
	uint8_t size;
};

struct X_509_unit {
	char company_name[128];
	char organization_unit[128];
	char organization[128];
	char location[128];
	char state[128];
	char country[2];
};

struct X_509_subject_pubkey_info {
	uint8_t enc_algo[16];
	uint8_t pubkey[4096];
	uint16_t size;
};

struct X_509_extensions {
	uint8_t cert_subject_key_id[20];
	uint8_t cert_authority_key_id[20];
	uint8_t cert_basic_constraints[128];
};

struct X_509_certificate_signature {
	uint8_t cert_signature_value[4096];
	uint16_t size;
};

struct X_509_certificate {
	uint8_t version;
	uint8_t serial_number[9];
	char cert_signature_alg[64];
	struct X_509_unit issuer;
	uint8_t valid_since[13];
	uint8_t valid_until[13];
	struct X_509_unit subject;
	struct X_509_subject_pubkey_info subject_pubkey_info;
	struct X_509_extensions extensions;
	struct X_509_certificate_signature cert_signature;
};

int x_509_issue_serial_number(struct X_509_certificate& cert);
int x_509_set_cert_signature_alg(struct X_509_certificate& cert, const char *algo);
int x_509_set_timestamp(struct X_509_certificate& cert, uint16_t days);
int x_509_set_issuer(struct X_509_certificate& cert, struct X_509_unit& issuer);
int x_509_set_subject(struct X_509_certificate& cert, struct X_509_unit& subject);
int x_509_set_subject_pubkey_info(struct X_509_certificate& cert,
		struct X_509_subject_pubkey_info& subject_pubkey_info);
int x_509_set_subject_pubkey_info(struct X_509_certificate& cert,
		struct X_509_certificate_signature& cert_signature);
int x_509_sign_certificate(struct X_509_certificate& cert);

#endif
