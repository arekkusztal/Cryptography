
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wmmintrin.h>

unsigned char key[16] = { 0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6d, 0x79, 0x20, 0x4b, 0x75,
		0x6e, 0x67, 0x20, 0x46, 0x75 };

uint8_t tab[10][16] = {
		{ 0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6d, 0x79, 0x20, 0x4b, 0x75,	0x6e, 0x67, 0x20, 0x46, 0x75 }
};

uint8_t AES_192_keys[10][20] = {
		{ 0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6d, 0x79, 0x20, 0x4b, 0x75,	0x6e, 0x67, 0x20, 0x46, 0x75, 0x54, 0xFA, 0x11, 0xAA }
};

unsigned char param[10] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36 };

unsigned char round_key[][16] = {
		{ 0x54,0x68,0x61,0x74,0x73,0x20,0x6D,0x79,0x20,0x4B,0x75,0x6E,0x67,0x20,0x46,0x75 },
		{ 0xE2,0x32,0xFC,0xF1,0x91,0x12,0x91,0x88,0xB1,0x59,0xE4,0xE6,0xD6,0x79,0xA2,0x93 },
		{ 0x56,0x08,0x20,0x07,0xC7,0x1A,0xB1,0x8F,0x76,0x43,0x55,0x69,0xA0,0x3A,0xF7,0xFA },
		{ 0xD2,0x60,0x0D,0xE7,0x15,0x7A,0xBC,0x68,0x63,0x39,0xE9,0x01,0xC3,0x03,0x1E,0xFB },
		{ 0xA1,0x12,0x02,0xC9,0xB4,0x68,0xBE,0xA1,0xD7,0x51,0x57,0xA0,0x14,0x52,0x49,0x5B },
		{ 0xB1,0x29,0x3B,0x33,0x05,0x41,0x85,0x92,0xD2,0x10,0xD2,0x32,0xC6,0x42,0x9B,0x69 },
		{ 0xBD,0x3D,0xC2,0x87,0xB8,0x7C,0x47,0x15,0x6A,0x6C,0x95,0x27,0xAC,0x2E,0x0E,0x4E },
		{ 0xcc,0x96,0xed,0x16,0x74,0xea,0xaa,0x03,0x1e,0x86,0x3f,0x24,0xb2,0xa8,0x31,0x6a },
		{ 0x8E,0x51,0xEF,0x21,0xFA,0xBB,0x45,0x22,0xE4,0x3D,0x7A,0x06,0x56,0x95,0x4B,0x6C },
		{ 0xBF,0xE2,0xBF,0x90,0x45,0x59,0xFA,0xB2,0xA1,0x64,0x80,0xB4,0xF7,0xF1,0xCB,0xD8 },
		{ 0x28,0xFD,0xDE,0xF8,0x6D,0xA4,0x24,0x4A,0xCC,0xC0,0xA4,0xFE,0x3B,0x31,0x6F,0x26 }
};

unsigned char round_key_0[16] = { 0x54,0x68,0x61,0x74,0x73,0x20,0x6D,0x79,0x20,0x4B,0x75,0x6E,0x67,0x20,0x46,0x75 };
unsigned char round_key_1[16] = { 0xE2,0x32,0xFC,0xF1,0x91,0x12,0x91,0x88,0xB1,0x59,0xE4,0xE6,0xD6,0x79,0xA2,0x93 };
unsigned char round_key_2[16] = { 0x56,0x08,0x20,0x07,0xC7,0x1A,0xB1,0x8F,0x76,0x43,0x55,0x69,0xA0,0x3A,0xF7,0xFA };
unsigned char round_key_3[16] = { 0xD2,0x60,0x0D,0xE7,0x15,0x7A,0xBC,0x68,0x63,0x39,0xE9,0x01,0xC3,0x03,0x1E,0xFB };
unsigned char round_key_4[16] = { 0xA1,0x12,0x02,0xC9,0xB4,0x68,0xBE,0xA1,0xD7,0x51,0x57,0xA0,0x14,0x52,0x49,0x5B };
unsigned char round_key_5[16] = { 0xB1,0x29,0x3B,0x33,0x05,0x41,0x85,0x92,0xD2,0x10,0xD2,0x32,0xC6,0x42,0x9B,0x69 };
unsigned char round_key_6[16] = { 0xBD,0x3D,0xC2,0x87,0xB8,0x7C,0x47,0x15,0x6A,0x6C,0x95,0x27,0xAC,0x2E,0x0E,0x4E };
unsigned char round_key_7[16] = { 0xcc,0x96,0xed,0x16,0x74,0xea,0xaa,0x03,0x1e,0x86,0x3f,0x24,0xb2,0xa8,0x31,0x6a };
unsigned char round_key_8[16] = { 0x8E,0x51,0xEF,0x21,0xFA,0xBB,0x45,0x22,0xE4,0x3D,0x7A,0x06,0x56,0x95,0x4B,0x6C };
unsigned char round_key_9[16] = { 0xBF,0xE2,0xBF,0x90,0x45,0x59,0xFA,0xB2,0xA1,0x64,0x80,0xB4,0xF7,0xF1,0xCB,0xD8 };
unsigned char round_key_10[16] = { 0x28,0xFD,0xDE,0xF8,0x6D,0xA4,0x24,0x4A,0xCC,0xC0,0xA4,0xFE,0x3B,0x31,0x6F,0x26 };
unsigned char round_key_p[16] = { };

unsigned char datablock[16] = { 0x54,0x77,0x6F,0x20,0x4F,0x6E,0x65,0x20,0x4E,0x69,0x6E,0x65,0x20,0x54,0x77,0x6F };

#define aes_key_genassist(arg) 		asm volatile(   \
									"aeskeygenassist $"arg", %xmm0, %xmm1;" \
									); \
									break;


static inline
uint64_t rdpmc(void)
{
	union {
		uint64_t val;
		struct {
			uint32_t lo_32;
			uint32_t hi_32;
		};
	} tsc;

	asm volatile("rdtsc"
			: "=a" (tsc.lo_32), "=d" (tsc.hi_32)
			: "c" (0xFA)
			: "memory"
			);

	return tsc.val;
}
/* FPU x87 */
inline double sinus(double f)
{
	f = 3.14*30/180;
	asm volatile (
			"fldl %0;"
			"fsin;"
			"fstpl %0;"
			: "+m" (f)
	);
	printf("\nResult %10.3f",sinus(f));
	return f;
}

void aesenc(void)
{
	asm volatile (
			"aesenc %xmm0, %xmm1"
	);
}

void print_binary(void *p, int size, const char *name)
{
	int i;

//	printf("\n%s: ", name);
	for (i=size-1;i>=0;i--) {
		printf("%u",*(int*)p >> i & 1);
		if ((i) % 8 == 0 && i)
			printf(" ");
	}
	printf("\n");

}

int get_registers_x86(void *flags)
{
	if (flags != NULL) {
		uint8_t al;
		asm volatile(
				"movb $255, %al;"
				"incb %al;"
				"incb %al;"
		);

		asm volatile(
				"pushfw;"
				"popw %0; "
				: "=m" (*(uint16_t*)flags)
		);
	}
}


void aes_enc(void)
{
	int i;
	printf("\nDATABLOCK: ");
	for (i = 0; i<sizeof(datablock); ++i) {
		printf("%02x ",datablock[i]);
	}
	printf("\n");

	asm volatile(
			"movdqu %[in], %%xmm15;"
			"movdqu %[xmm0_in], %%xmm0;"
			"movdqu %[xmm1_in], %%xmm1;"
			"movdqu %[xmm2_in], %%xmm2;"
			"movdqu %[xmm3_in], %%xmm3;"
			"movdqu %[xmm4_in], %%xmm4;"
			"movdqu %[xmm5_in], %%xmm5;"
			"movdqu %[xmm6_in], %%xmm6;"
			"movdqu %[xmm7_in], %%xmm7;"
			"movdqu %[xmm8_in], %%xmm8;"
			"movdqu %[xmm9_in], %%xmm9;"
			"movdqu %[xmm10_in], %%xmm10;"


		    "pxor %%xmm0, %%xmm15;"
			"aesenc %%xmm1, %%xmm15;"
			"aesenc %%xmm2, %%xmm15;"
			"aesenc %%xmm3, %%xmm15;"
			"aesenc %%xmm4, %%xmm15;"
			"aesenc %%xmm5, %%xmm15;"
			"aesenc %%xmm6, %%xmm15;"
			"aesenc %%xmm7, %%xmm15;"
			"aesenc %%xmm8, %%xmm15;"
			"aesenc %%xmm9, %%xmm15;"
			"aesenclast %%xmm10, %%xmm15;"
			"movdqu %%xmm15, %[out]"
		    : [out] "=m" (datablock)
		    : [in] "m" (datablock), [xmm0_in] "m" (round_key[0]), [xmm1_in] "m" (round_key[1]), [xmm2_in] "m" (round_key[2])
			  , [xmm3_in] "m" (round_key[3]), [xmm4_in] "m" (round_key[4]), [xmm5_in] "m" (round_key[5]), [xmm6_in] "m" (round_key[6])
			  , [xmm7_in] "m" (round_key[7]), [xmm8_in] "m" (round_key[8]), [xmm9_in] "m" (round_key[9]), [xmm10_in] "m" (round_key[10])
	);

	printf("\nDATABLOCK R: ");
	for (i = 0; i<sizeof(datablock); ++i) {
		printf("%02x ",datablock[i]);
	}
	printf("\n");



	asm volatile(
			"movdqu %[in], %%xmm15;"
			"movdqu %[xmm0_in], %%xmm0;"
			"movdqu %[xmm1_in], %%xmm1;"
			"movdqu %[xmm2_in], %%xmm2;"
			"movdqu %[xmm3_in], %%xmm3;"
			"movdqu %[xmm4_in], %%xmm4;"
			"movdqu %[xmm5_in], %%xmm5;"
			"movdqu %[xmm6_in], %%xmm6;"
			"movdqu %[xmm7_in], %%xmm7;"
			"movdqu %[xmm8_in], %%xmm8;"
			"movdqu %[xmm9_in], %%xmm9;"
			"movdqu %[xmm10_in], %%xmm10;"

		    "pxor %%xmm0, %%xmm15;"
			"aesdec %%xmm1, %%xmm15;"
			"aesdec %%xmm2, %%xmm15;"
			"aesdec %%xmm3, %%xmm15;"
			"aesdec %%xmm4, %%xmm15;"
			"aesdec %%xmm5, %%xmm15;"
			"aesdec %%xmm6, %%xmm15;"
			"aesdec %%xmm7, %%xmm15;"
			"aesdec %%xmm8, %%xmm15;"
			"aesdec %%xmm9, %%xmm15;"
			"aesdeclast %%xmm10, %%xmm15;"
			"movdqu %%xmm15, %[out]"
		    : [out] "=m" (datablock)
		    : [in] "m" (datablock), [xmm0_in] "m" (round_key[0]), [xmm1_in] "m" (round_key[1]), [xmm2_in] "m" (round_key[2])
			  , [xmm3_in] "m" (round_key[3]), [xmm4_in] "m" (round_key[4]), [xmm5_in] "m" (round_key[5]), [xmm6_in] "m" (round_key[6])
			  , [xmm7_in] "m" (round_key[7]), [xmm8_in] "m" (round_key[8]), [xmm9_in] "m" (round_key[9]), [xmm10_in] "m" (round_key[10])
	);

	printf("\nDATABLOCK: ");
	for (i = 0; i<sizeof(datablock); ++i) {
		printf("%02x ",datablock[i]);
	}

}

void AES_EBC_encrypt_instr(void)
{
	__m128i tmp;
	char out[16];
	int i;

	tmp = _mm_loadu_si128((__m128i*)datablock);
	tmp = _mm_xor_si128(tmp, *(__m128i*)round_key[0]);
	for (i = 0; i< 10; i++) {
	//	tmp = _mm_aesenc_si128(*(__m128i *)key, *(__m128i *)key);
	}
//	tmp = _mm_aesenclast_si128(tmp, tmp);
	_mm_storeu_si128((__m128i *)out, tmp);



}

void
AES_128_roundkey_generate(uint8_t p[][16])
{
	int i;

	for (i = 1; i<=10; ++i) {
		asm volatile(
				"movdqu %[in], %%xmm0;"
				:
				: [in] "m" (p[i-1])
		);
		switch (i) {
			case 1:
				aes_key_genassist("1");
			case 2:
				aes_key_genassist("2");
			case 3:
				aes_key_genassist("4");
			case 4:
				aes_key_genassist("8");
			case 5:
				aes_key_genassist("16");
			case 6:
				aes_key_genassist("32");
			case 7:
				aes_key_genassist("64");
			case 8:
				aes_key_genassist("128");
			case 9:
				aes_key_genassist("27");
			case 10:
				aes_key_genassist("54");
		}
		asm volatile(
				"pshufd $0xFF , %%xmm1, %%xmm1;\n"
				"shufps $0x10 , %%xmm0, %%xmm2;\n"
				"pxor   %%xmm2, %%xmm0		  ;\n"
				"shufps $0x8C , %%xmm0, %%xmm2;\n"
				"pxor   %%xmm2, %%xmm0		  ;\n"
				"pxor   %%xmm1, %%xmm0        ;\n"
				"movdqu %%xmm0, %[out]        ;\n"
				: [out] "=m" (p[i])
		);
	}

}

uint8_t *
AES_128_EBC_encrypt(uint8_t p[][16], uint8_t *data)
{
	int i;
	asm volatile(
			"movdqu %[in] , %%xmm1;"
			"movdqu %[key], %%xmm0;"
		    "pxor   %%xmm0, %%xmm1;"
			:
			: [in] "m" (datablock), [key] "m" (*tab)
	);

	for (i = 1; i<10; i++) {
		asm volatile(
			"movdqu %[key], %%xmm0;"
			"aesenc %%xmm0, %%xmm1;"
			:
			: [key] "m" (tab[i])
		);
	}

	asm volatile (
			"movdqu 	%[key], %%xmm0   ;"
			"aesenclast %%xmm0, %%xmm1   ;"
			"movdqu 	%%xmm1, %[cipher];"
			: [cipher] "=m" (datablock)
			: [key]     "m" (tab[i])
	);



	return NULL;
}

#define AES_128_EBC_ENCRYPT_
#define SIMD_INSTRUCTION_SET

union {
	uint8_t array[16];
	struct {
		double lo;
		double hi;
	};
} packed_dbl;

void
SIMD_instruction_set(void)
{
	packed_dbl.lo = 5.5;
	packed_dbl.hi = 2.2;

	printf("\nlo: %f, hi: %f", packed_dbl.lo, packed_dbl.hi);

	asm volatile(
			"movdqu   %0, %%xmm0         ;"
			"movdqu   %0, %%xmm1         ;"
			"addsubpd %%xmm1, %%xmm0 ;"
			"movaps   %%xmm0, %0     ;"
			"vmovdqu  %0, %%ymm0	  				 ;"
			: "+m" (packed_dbl.array)
	);

	printf("\nlo: %f, hi: %f", packed_dbl.lo, packed_dbl.hi);
}


union {
	uint64_t b;
	uint8_t array[8];
} bsw;

#define AES_128_EBC_ENCRYPT_

int main(int argc, char *argv[])
{
	int res = 0, i, j;
	uint64_t start_1 = 0;
	uint64_t stop_2 = 0;

	start_1 = rdpmc();
	stop_2 = rdpmc();

	printf("\nTimestamp : %lu\n",stop_2 - start_1);

	return 0;
//	SIMD_instruction_set();

	uint64_t start = rdpmc();

#ifdef AES_128_EBC_ENCRYPT
	AES_128_roundkey_generate(tab);

/*	for (j=0;j<=10;j++) {
		for (i = 0; i<16; ++i) {
			printf("%02x ",tab[j][i]);
		}
		printf("\n");
	}

	printf("\nDATA BLOCK: \t");
	for (i = 0; i<sizeof(datablock); ++i) {
		printf("%02x ",datablock[i]);
	} */

	AES_128_EBC_encrypt(NULL, NULL);
	AES_128_EBC_encrypt(NULL, NULL);
	AES_128_EBC_encrypt(NULL, NULL);
	AES_128_EBC_encrypt(NULL, NULL);

/*	printf("\nCIPHER BLOCK: \t");
	for (i = 0; i<sizeof(datablock); ++i) {
		printf("%02x ",datablock[i]);
	} */
#endif

	uint64_t stop = rdpmc();
	printf("\ncycles %lu ",stop-start);

	return 0;
}




