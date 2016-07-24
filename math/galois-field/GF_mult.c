#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t x[] = {
    0x1, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x8, 0x4, 0x3, 0x80,
};

uint8_t y[] = {
    0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
};

uint8_t result[] = {
		0x13, 0xE0, 0x67, 0x6C, 0x67, 0x6C, 0x67, 0x6C,
		0x67, 0x6C, 0x67, 0x6C, 0x67, 0x63, 0x45, 0x57,
};



static inline void
XOR(uint8_t *A, uint8_t *B, uint16_t size)
{
	int i;
	for (i =0;i<size; i++)
	{
		*((uint64_t *)A + i) ^= *((uint64_t *)B + i);
	}
}

static inline void
shift_right(uint8_t *A, uint16_t size)
{
	int i;
    for (i = size-1; i >= 0; i--)
    {
	    A[i] = (A[i] >> 1) & 0x7F;

	    if (i && (A[i - 1] & 1))
	    {
		    A[i] |= (1 << 7);
	    }
    }
}

static void
GF_mult(uint8_t *Z, uint8_t *X, uint8_t *Y)
{
      int i, j, k;
      uint8_t V[16];

      memset(Z, 0, 16);
      memcpy(V, X, 16);

      for (i = 0; i < 16; ++i)
      {
		for (k=0; k<8; k++) {
			if (Y[i] & (1 << (7 - (k & 0x7))))
			{
				XOR(Z, V, 2);
			}

			if (V[15] & 1) {
				shift_right(V, 16);
				V[0] ^= 0xE1;
			}
			else
			{
				shift_right(V, 16);
			}
		}

      }
}

int main()
{
      int i;
      uint8_t *r = malloc(16);

      GF_mult(r, x, y);
      for (i = 0 ; i< 16; i++){
		 if (i && (i % 8 == 0))
			 printf("\n");
		 printf("0x%02X, ", r[i]);
      }
      printf("\n");

      memset(r, 0, 16);
      free(r);
      return 0;
}


/* REFERENCES
 * 1. http://csrc.nist.gov/groups/ST/toolkit/BCM/documents/proposedmodes/gcm/gcm-spec.pdf
 * */

