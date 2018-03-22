#ifndef AES_CTR_TEST_VECTORS_H
#define AES_CTR_TEST_VECTORS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum OP {
	ADD = 1,
	SUB,
	MULT,
	DIV,
   MOD,
   LSH,
   RSH,
};


struct long_number_vector
{
	const char *name;
	enum OP op;
	struct {
		unsigned char data[1024];
		uint16_t size [1024];
	} A;

	struct {
		unsigned char data[1024];
		uint16_t size [1024];
	} B;

	struct {
		unsigned char data[1024];
		uint16_t size [1024];
   } R;
   uint16_t lsh;
};

static struct long_number_vector long_numbers_shift_vectors[] =
{
    {
    	"LEFT_SHIFT_vector_1_LSH_120",
        LSH,
        {
            "0x10E",
            2
        },
        {
        },
        {
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E,
            16
        },
        120,
    },
    {
    	"LEFT_SHIFT_vector_1_LSH_117",
        LSH,
        {
            "1521534435",
            sizeof("1521534435")
        },
        {
            /* Unused */
        },
        {
    			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x86,
        },
        117
    }
};

static struct long_number_vector long_numbers_add_vectors[] =
{
    {
    	"ADD_vector_10E_75E4",
        LSH,
        {
            "10E",
            2
        },
        {
        		"75E4",
        		2
        },
        {
			0x78, 0x56, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			//"7C5678",
            3
        },
    },
    {
    	"ADD_vector_10E_75E4",
        LSH,
        {
            "FFAE",
            2
        },
        {
        		"75E4",
        		2
        },
        {
			0x78, 0x56, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			//"7C5678",
            3
        },
    },
};

static struct long_number_vector long_numbers_mult_vectors[] =
{
    {
    	"MULT_vector_10E_75E4",
        LSH,
        {
            "10E",
            2
        },
        {
        		"75E4",
        		2
        },
        {
			0x78, 0x56, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			//"7C5678",
            3
        },
    },
    {
    	"MULT_vector_F13410E_A1243FF5E4",
        LSH,
        {
           "F13410E",
            4
        },
        {
        	"A1243FF5E4",
        	5
        },
        {
			0x78, 0x56, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			//"7C5678",
            3
        },
    },
};
/*
static struct long_number_vector long_number_add_1 = {
      ADD,
		{
				"12254412",
				4
		},
    {
    },
    {
    },
    0

}; */
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
#ifdef __cplusplus
}
#endif

#endif
