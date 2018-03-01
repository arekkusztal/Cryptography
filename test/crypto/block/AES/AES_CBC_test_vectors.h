#ifndef AES_CBC_TEST_VECTORS_H
#define AES_CBC_TEST_VECTORS_H

#include <stdint.h>
#include <CRYPTO_LIB_common.h>

struct AES_test_vector
{
	enum mode mode;
	uint8_t iv[16];
	struct {
		uint8_t data[32];
		uint8_t len;
	} key;
	struct
	{
		uint8_t data[4096];
		uint16_t len;
	} plaintext;
	struct
	{
		uint8_t data[4096];
		uint16_t len;
	} ciphertext;
};

struct AES_test_vector AES_test_vector_1 = {
		.mode = CBC,
		.iv = { 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00 },
		.key = {
				.data = {
				0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6d, 0x79, 0x20, 0x4b, 0x75,
						0x6e, 0x67, 0x20, 0x46, 0x75 },
				.len = 16
		},
		.plaintext = {
				.data = {
						0x54, 0x77, 0x6F, 0x20, 0x4F, 0x6E, 0x65, 0x20,
						0x4E, 0x69, 0x6E, 0x65, 0x20, 0x54, 0x77, 0x6F,
						0x54, 0x77, 0x6F, 0x20, 0x4F, 0x6E, 0x65, 0x20,
						0x4E, 0x69, 0x6E, 0x35, 0x20, 0x54, 0x77, 0x6F },
				.len = 32
		},
		.ciphertext = {
				.data = {
						0x3D, 0x4C, 0x64, 0x11, 0x25, 0x80, 0x2A, 0x3F,
						0xD9, 0x49, 0xBD, 0x59, 0x5E, 0xA0, 0x07, 0x8B,
						0xDB, 0xF4, 0x0D, 0x64, 0x80, 0xC6, 0x21, 0x33,
						0xE1, 0xEC, 0xC6, 0xA4, 0x1B, 0x4E, 0xF4, 0x18
				},
				.len = 32
		}

};

/* Borrowed from DPDK xP */
struct AES_test_vector AES_test_vector_cbc_128 = {
		.mode = CBC,
		.iv = {
				0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
				0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
		},
		.key = {
				.data = {
						0xE4, 0x23, 0x33, 0x8A, 0x35, 0x64, 0x61, 0xE2,
						0x49, 0x03, 0xDD, 0xC6, 0xB8, 0xCA, 0x55, 0x7A
				},
				.len = 16
		},
		.plaintext = {
				.data = {
						"What a lousy earth! He wondered how many people "
						"were destitute that same night even in his own "
						"prosperous country, how many homes were "
						"shanties, how many husbands were drunk and "
						"wives socked, and how many children were "
						"bullied, abused, or abandoned. How many "
						"families hungered for food they could not "
						"afford to buy? How many hearts were broken? How "
						"many suicides would take place that same night, "
						"how many people would go insane? How many "
						"cockroaches and landlords would triumph? How "
						"many winners were losers, successes failures, "
						"and rich men poor men? How many wise guys were "
						"stupid? How many happy endings were unhappy "
						"endings? How many honest men were liars, brave "
						"men cowards, loyal men traitors, how many "
						"sainted men were corrupt, how many people in "
						"positions of trust had sold their souls to "
						"bodyguards, how many had never had souls? How "
						"many straight-and-narrow paths were crooked "
						"paths? How many best families were worst "
						"families and how many good people were bad "
						"people? When you added them all up and then "
						"subtracted, you might be left with only the "
						"children, and perhaps with Albert Einstein and "
						"an old violinist or sculptor somewhere."
				},
				.len = 512
		},
		.ciphertext = {
				.data = {

				},
				.len = 512
		}
};

#endif

