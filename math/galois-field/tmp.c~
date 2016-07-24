#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define OSAL_HOST_TO_NW_64(uData)  \
    ((((uData) >> 56) & 0xffull) \
     | (((uData) >> 40) & 0x000000000000ff00ull) \
     | (((uData) >> 24) & 0x0000000000ff0000ull) \
     | (((uData) >> 8)  & 0x00000000ff000000ull) \
     | (((uData) << 56)  & 0xff00000000000000ull) \
     | (((uData) << 40) & 0x00ff000000000000ull) \
     | (((uData) << 24) & 0x0000ff0000000000ull) \
     | (((uData) << 8) & 0x000000ff00000000ull))


uint8_t H[16] = {
      0xB8, 0x3B, 0x53, 0x37, 0x08, 0xBF, 0x53, 0x5D, 0x0A, 0xA6, 0xE5, 0x29, 0x80, 0xD5, 0x3B, 0x78
};

uint8_t IV[8] = {
      0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad,
};


static void
GF_mult(uint8_t *Z, uint8_t *X, uint8_t *Y)
{
      int i, j;
      uint8_t v127;
      uint8_t V[16];

      memset(Z, 0, 16);
      memcpy(V, X, 16);

      for (i = 0; i <= 127; ++i)
      {
	   v127 = (V[15] & 1);
	   if (Y[i >> 3] & (1 << (7 - (i & 0x7))))
	   {
	       for (j = 0; j < 16; j++)
	       {
	           Z[j] ^= V[j];
	       }
	   }

	   for (j = 15; j >= 0; j--)
	   {
	       V[j] = (V[j] >> 1) & 0x7F;

	       if (j && (V[j - 1] & 1))
	       {
	           V[j] |= (1 << 7);
	       }
	   }

	   if (v127)
	   {

	       V[0] ^= 0xE1;
	   }
      }
}

static
void multiplicationInGf(
    uint8_t * x,
    uint8_t * y,
    uint8_t * z)
{
    uint8_t v[16];
    int i, j;

    /* Z <- 0, V <- X */
    memset(z, 0, 16);
    memcpy(v, x, 16);

    /* for i = 0 to 127 do */
    for (i = 0; i <= 127; i++)
    {
        uint8_t v127 = (v[15] & 1);

        /* if Yi = 1 then */
        if (y[i >> 3] & (1 << (7 - (i & 0x7))))
        {
            /* Z <- Z (+) V */
            for (j = 0; j < 16; j++)
            {
                z[j] ^= v[j];
            }
        } /* end if */

        /* V <- rightshift(V) */
        for (j = 15; j >= 0; j--)
        {
            v[j] = (v[j] >> 1) & 0x7F;

            if (j && (v[j - 1] & 1))
            {
                v[j] |= (1 << 7);
            }
        }

        /* if V127 == 1 then */
        if (v127)
        {
            /* V <- V (+) R */
            v[0] ^= 0xE1;
        } /* end if */
    } /* end for */
}


static void ghash_internal_2(
    uint8_t * R,
    uint8_t * pKey,
    uint8_t * pInput, int inputLen)
{
    uint8_t x[16];

    int i, j;

    memset(R, 0, 16);

    for (i = 0; i < inputLen; i += 16)
    {
        memcpy(x, R, 16);

        for (j = 0; j < 16; j++)
        {
            x[j] ^= pInput[i + j];
        }

        GF_mult(R, x, pKey);
    }
}

static void ghash_2(
    uint8_t * R,
    uint8_t * pH,
    uint8_t * pA, uint64_t aLen,
    uint8_t * pC, uint64_t cLen)
{
    int aPadLen = ((aLen & 15) ? 16 - (aLen & 15) : 0);
    int cPadLen = ((cLen & 15) ? 16 - (cLen & 15) : 0);
    int dataLen = aLen + aPadLen + cLen + cPadLen + 16;

    uint8_t * pData = malloc(dataLen);
    uint8_t * pDataA = pData;
    uint8_t * pDataC = pDataA + aLen + aPadLen;
    uint8_t * pDataL = pDataC + cLen + cPadLen;

    memcpy(pDataA, pA, aLen);
    memset(pDataA + aLen, 0, aPadLen);
    memcpy(pDataC, pC, cLen);
    memset(pDataC + cLen, 0, cPadLen);
    *(uint64_t *)(pDataL + 0) = OSAL_HOST_TO_NW_64(aLen * 8);
    *(uint64_t *)(pDataL + 8) = OSAL_HOST_TO_NW_64(cLen * 8);

    ghash_internal_2(R, pH, pData, dataLen);

    free(pData);
}







/*
 * Perform GHASH(key, input)
 */
static void ghash_internal(
    uint8_t * pKey,
    uint8_t * pInput, int inputLen,
    uint8_t * pOutput)
{
    uint8_t x[16];

    int i, j;

    memset(pOutput, 0, 16);

    for (i = 0; i < inputLen; i += 16)
    {
        memcpy(x, pOutput, 16);

        for (j = 0; j < 16; j++)
        {
            x[j] ^= pInput[i + j];
        }

        multiplicationInGf(x, pKey, pOutput);
    }
}

/*
 * Perform GHASH(H, A, C)
 */
static void ghash(
    uint8_t * pH,
    uint8_t * pA, uint64_t aLen,
    uint8_t * pC, uint64_t cLen,
    uint8_t * pResult)
{
    int aPadLen = ((aLen & 15) ? 16 - (aLen & 15) : 0);
    int cPadLen = ((cLen & 15) ? 16 - (cLen & 15) : 0);
    int dataLen = aLen + aPadLen + cLen + cPadLen + 16;

    uint8_t * pData = malloc(dataLen);
    uint8_t * pDataA = pData;
    uint8_t * pDataC = pDataA + aLen + aPadLen;
    uint8_t * pDataL = pDataC + cLen + cPadLen;

    memcpy(pDataA, pA, aLen);
    memset(pDataA + aLen, 0, aPadLen);
    memcpy(pDataC, pC, cLen);
    memset(pDataC + cLen, 0, cPadLen);
    *(uint64_t *)(pDataL + 0) = OSAL_HOST_TO_NW_64(aLen * 8);
    *(uint64_t *)(pDataL + 8) = OSAL_HOST_TO_NW_64(cLen * 8);

    ghash_internal(pH, pData, dataLen, pResult);

    free(pData);
}

uint8_t x[] = {
    0x1, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x8, 0x4, 0x3, 0x80,
};

uint8_t y[] = {
    0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
};

int main()
{
      int i;
      uint8_t *iv_out = malloc(32);
      uint8_t *r = malloc(16);
  //    ghash_2(iv_out, H, NULL, 0, IV, 8);
  //    ghash(H, NULL, 0, IV, 8, iv_out);


 /*
      for (i = 0 ; i< 32; i++){
	 if (i && (i % 8 == 0))
	     printf("\n");
	 printf("0x%02X, ", iv_out[i]);


      }*/

 /*
      multiplicationInGf(x, y, r);


      for (i = 0 ; i< 16; i++){
	 if (i && (i % 8 == 0))
	     printf("\n");
	 printf("0x%02X, ", r[i]);

      }
      printf("\n\n");
 */
      GF_mult(r, x, y);
      for (i = 0 ; i< 16; i++){
	 if (i && (i % 8 == 0))
	     printf("\n");
	 printf("0x%02X, ", r[i]);
      }
      printf("\n");

      return 0;
}



/*
 *
 * static void ghash_internal(
    uint8_t * pKey,
    uint8_t * pInput, int inputLen,
    uint8_t * pOutput)
{
    uint8_t x[16];

    int i, j;

    memset(pOutput, 0, 16);

    for (i = 0; i < inputLen; i += 16)
    {
        memcpy(x, pOutput, 16);

        for (j = 0; j < 16; j++)
        {
            x[j] ^= pInput[i + j];
        }

        multiplicationInGf(x, pKey, pOutput);
    }
}
 */


