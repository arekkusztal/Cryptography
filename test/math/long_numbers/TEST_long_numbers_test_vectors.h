#ifndef AES_CTR_TEST_VECTORS_H
#define AES_CTR_TEST_VECTORS_H

#include <stdint.h>

enum OP {
	ADD = 1,
	SUB,
	MULT,
	DIV,
	MOD
};


struct long_number_vector
{
	enum OP op;
	struct {
		uint8_t data[1024];
		uint16_t size [1024];
	} A;

	struct {
		uint8_t data[1024];
		uint16_t size [1024];
	} B;

	struct {
		uint8_t data[1024];
		uint16_t size [1024];
	} R;
};

static struct long_number_vector long_number_add_1 = {
		ADD,
		{
				"12254412",
				4
		},
};
/*	.op = ADD,
	.A = {
		.data = "12254412",
		.size = 4
	},
	.B = {
		.data = "162207FA",
		.size = 4
	},
}; */
/*
static struct long_number_vector long_number_add_2 = {
	.op = ADD,
	.A = {
		.data = "FFF112254412",
		.size = 6
	},
	.B = {
		.data = "4111162207FA",
		.size = 6
	},
};

static struct long_number_vector long_number_add_3 = {
	.op = ADD,
	.A = {
		.data = "AF2511AF4125FFF112254412",
		.size = 12
	},
	.B = {
		.data = "248903EF23098A987BB12938",
		.size = 12
	},
};

static struct long_number_vector long_number_mult_1 = {
	.op = ADD,
	.A = {
		.data = "12254412",
		.size = 4
	},
	.B = {
		.data = "162207FA",
		.size = 4
	},
};

static struct long_number_vector long_number_mult_2 = {
	.op = ADD,
	.A = {
		.data = "FFF112254412",
		.size = 6
	},
	.B = {
		.data = "4111162207FA",
		.size = 6
	},
};

static struct long_number_vector long_number_mult_3 = {
	.op = ADD,
	.A = {
		.data = "AF2511AF4125FFF112254412",
		.size = 12
	},
	.B = {
		.data = "248903EF23098A987BB12938",
		.size = 12
	},
};
*/

#endif
