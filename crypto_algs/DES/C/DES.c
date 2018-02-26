#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void hex_dump(const char *def, uint8_t *data, uint16_t len,
		uint16_t br);

void print_binary(void *p, int size, int chunks, const char *name)
{
	int i, k;
	uint8_t *ar = p;

	printf("\n%s: \n", name);
	for (k =0; k< chunks; k++) {
		if (k && k % 4 == 0)
			printf("\n");
		for (i=size-1;i>=0;i--) {
			printf("%u",*(int*)&ar[k] >> i & 1);
			if (i == 0)
				printf(" ");
		}
	}
	printf("\n");

}

int S1[] = {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
			 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
			 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
			15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13};

int S2[] = {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
			 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
			 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
			13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9};

int S3[] = {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
			13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
			13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
			 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

int S4[] = { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
			13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
			10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
			 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14};

int S5[] = { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
			14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
			 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
			11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3};

int S6[] = {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
			10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
			 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
			 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};

int S7[] = { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
			13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
			 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
			 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12};

int S8[] = {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
			 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
			 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
			 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11};

uint8_t sel[48];

uint8_t PC_1[] = {
		57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4
};

uint8_t PC_2[] = {
		14 ,   17  ,  11 ,    24  ,    1  ,   5,
		 3   ,  28  ,  15   ,   6  ,   21  ,  10,
		 23  ,   19 ,   12  ,    4  ,   26  ,   8,
		 16   ,   7 ,   27  ,   20 ,    13  ,   2,
		 41  ,   52  ,  31  ,   37  ,   47  ,  55,
		 30  ,   40  ,  51  ,   45  ,   33 ,   48,
		 44  ,   49  ,  39  ,   56  ,   34 ,   53,
		 46   ,  42  ,  50  ,   36  ,   29  ,  32
};

uint8_t PC_I[] =	   {58, 50, 42, 34, 26, 18, 10, 2,
										60, 52, 44, 36, 28, 20, 12, 4,
										62, 54, 46, 38, 30, 22, 14, 6,
										64, 56, 48, 40, 32, 24, 16, 8,
										57, 49, 41, 33, 25, 17,  9, 1,
										59, 51, 43, 35, 27, 19, 11, 3,
										61, 53, 45, 37, 29, 21, 13, 5,
										63, 55, 47, 39, 31, 23, 15, 7};

int E_Bit[] =  {32,  1,  2,  3,  4,  5,
							 4,  5,  6,  7,  8,  9,
							 8,  9, 10, 11, 12, 13,
							12, 13, 14, 15, 16, 17,
							16, 17, 18, 19, 20, 21,
							20, 21, 22, 23, 24, 25,
							24, 25, 26, 27, 28, 29,
							28, 29, 30, 31, 32,  1};

uint8_t P[] = {
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF
};

uint8_t P_2[8];

uint8_t K[] = {
		0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1
};

int PERM[] =    {16,  7, 20, 21,
									29, 12, 28, 17,
									 1, 15, 23, 26,
									 5, 18, 31, 10,
									 2,  8, 24, 14,
									32, 27,  3,  9,
									19, 13, 30,  6,
									22, 11,  4, 25};

uint8_t kplus[8];
uint8_t ectB[8];

uint8_t Kp[56];
uint8_t C[17][28];
uint8_t D[17][28];

uint8_t CD[17][56];

uint8_t sub_k[16][48];

uint8_t subkeys[16][6];

union  {
	struct {
		uint32_t L;
		uint32_t R;
	};
	uint64_t LRN;
} LR[16];

uint8_t EX_R[16][6];

void
rotate(uint8_t *out, uint8_t *data, uint16_t base, uint16_t len)
{
	int i;
	for (i = 0; i < base; i++)
	{
		out[(base - len + i) % base] = data[i];
	}
}

void PC_2_sub(uint8_t *data)
{
	int i, k;
	for (k = 1; k< 17; k++) {
		for (i = 0; i< 48; i++)
		{
			if (CD[k][PC_2[i]-1]) {
				subkeys[k-1][i/8] |= 1 << ( 7 -(i % 8));
			//	sub_k[0][i] = 1;
			}
		}
	}
}

void PC_I_sub(uint8_t *data)
{
	int i, k, t=7;
	for (i = 0; i< 64; i++)
	{
		if ((data[PC_I[i]/8] >> (8 - (PC_I[i] % 8)) ) & 1) {
			P_2[i/8] |= 1 << ( 7 -(i % 8));
		}
		else if (PC_I[i] % 8 == 0){
			P_2[i/8] |= (data[PC_I[i]/8] & 1) << t--;
		}
	}
}

void E_Bit_sel(uint8_t *data)
{
	int i, k, t=7;
	for (i = 0; i< 48; i++)
	{
		if ((data[E_Bit[i]/8] >> (8 - (E_Bit[i] % 8)) ) & 1) {
			EX_R[0][i/8] |= 1 << ( 7 -(i % 8));
		}
		else if (E_Bit[i] % 8 == 0){
			EX_R[0][i/8] |= (data[E_Bit[i]/8] & 1) << t--;
		}
	}
}

void
expand_binary(uint8_t *out,uint8_t *in)
{
	int i;
	printf("\n");
	for (i =0;i<48; i++){
		sel[i] = ( (in[i >> 3] >> (7 - (i & 7))) & 1);
	}
}

void
weird(uint8_t *out, uint8_t *in)
{
	int i;
	uint8_t A = 0,B = 0;
	uint32_t temp = 0;
	for (i=0;i<8;i++) {
		A |= (in[i*6] << 1) | (in[i*6+5]);
		B |= (in[i*6 + 1] << 3 ) | (in[i*6 + 2] << 2 ) | (in[i*6 + 3] << 1 ) | (in[i*6 + 4] );
		printf("\nA: %d",A);
		printf("\nB: %d",B);
		if (i == 0) {
			temp = S1[A*16+B];
			//*out |= (temp << (4));
			out[0] |= temp << 4;
			printf("\nS(1) = %d", S1[A*16+B]);
		}
		else if (i == 1) {
			temp = S2[A*16+B];
			out[0] |= temp;
		//	*out |= (temp << (28 -i*4));
			printf("\nS(2) = %d", S2[A*16+B]);
		}
		else if (i == 2) {
			temp = S3[A*16+B];
			out[1] |= temp << 4;
		//	*out |= (temp << (28 -i*4));
			printf("\nS(2) = %d", S3[A*16+B]);
		}
		else if (i == 3) {
			temp = S4[A*16+B];
			out[1] |= temp;
			printf("\nS(2) = %d", S4[A*16+B]);
		}
		else if (i == 4) {
			temp = S5[A*16+B];
			out[2] |= temp << 4;
			printf("\nS(2) = %d", S5[A*16+B]);
		}
		else if (i == 5) {
			temp = S6[A*16+B];
			out[2] |= temp;
			printf("\nS(2) = %d", S6[A*16+B]);
		}
		else if (i == 6) {
			temp = S7[A*16+B];
			out[3] |= temp << 4;
			printf("\nS(2) = %d", S7[A*16+B]);
		}
		else if (i == 7) {
			temp = S8[A*16+B];
			out[3] |= temp;
			printf("\nS(2) = %d", S8[A*16+B]);
		}
		temp = 0;

		A =0;
		B = 0;
	}
}
/*
int main()
{

	int i, j;
	for (i =0;i<56;i++)
	{
		if ( (K[PC_1[i]/8] >> (8 - (PC_1[i] % 8)) ) & 1) {
	//		kplus[i/8] |= 1 << ( 7 -(i % 8));
			Kp[i] = 1;
		}
	}

	printf("\n **************** DES ****************** \n");
	memcpy(C[0], Kp, 28);
	memcpy(D[0], &Kp[28], 28);
	memcpy(CD[0], Kp, 56);

//	print_binary(K, 8, 8, "Key");
//	print_binary(kplus, 8, 8, "kplus");

//	hex_dump("C0", C[0], 28, 28);
//	hex_dump("D0", D[0], 28, 28);

	for (i =1; i<=16; i++)
	{
		if (i == 1 || i == 2 || i ==9 || i ==16) {
			rotate(CD[i], CD[i-1], 28, 1);
			rotate(&CD[i][28], &CD[i-1][28], 28, 1);
		}
		else
		{
			rotate(CD[i], CD[i-1], 28, 2);
			rotate(&CD[i][28], &CD[i-1][28], 28, 2);
		}
//		printf("\n - %d",i);
//		hex_dump("C", CD[i], 28, 28);
//		hex_dump("D", &CD[i][28], 28, 28);
	}

	PC_2_sub(NULL);
	//hex_dump("sub_k[0]", sub_k[0], 56, 28);
	for (i =0 ;i<16;i++) {
//		printf("\n%i --", i);
//		print_binary(subkeys[i], 8, 6,"\nSubkey 1");
	}

	PC_I_sub(P);
	print_binary(P_2, 8, 8, "P_2");

	LR[0].L = *(uint32_t*)(P_2);
	LR[0].R = *(uint32_t*)(P_2 + 4);


	print_binary(&LR[0].L, 8, 4, "L_0");
	print_binary(&LR[0].R, 8, 4, "R_0");

	for (i =1 ; i< 16; i++) {
		LR[i].L = LR[i-1].R;
		LR[i].R = LR[i-1].L ; // + f
	}

	E_Bit_sel((uint8_t *)&LR[0].R);

	print_binary(EX_R[0], 8, 6, "E(R_0)");

	for (j =0; j < 16; j++) {
		for (i =0 ; i< 6; i++) {
			EX_R[j][i] ^= subkeys[j][i];
		}
	}

	print_binary(EX_R[0], 8, 6, "E(R_0)");
	printf("\n");
	expand_binary(sel, EX_R[0]);

	uint32_t f = 0;
	uint8_t f_2[4] = { 0 };
	hex_dump("sel", sel, 48, 16);
	weird((uint8_t *)&f_2, sel);
	print_binary(&f_2,8,4, "f");
	return 0;
} */
