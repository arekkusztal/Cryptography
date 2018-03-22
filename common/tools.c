#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

void hex_dump(const char *def, uint8_t *data, uint16_t len,
		uint16_t br)
{
	uint16_t i;

	printf("\n%s:\n", def);
	for (i = 0; i < len; ++i) {
		if (i && ( i % br ==0 ))
			printf("\n");
		printf("0x%02X ",data[i]);
	}
	printf("\n");
}

void bit_dump_b(uint8_t data)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{
		printf("%d", (data >> (7 - i)) & 1);
	}
	printf("\n");
}

void bit_dump_s(uint8_t *data, int size)
{
	uint8_t i;
	int j;

   int org_size = size;
   size += 7;
   size &= ~7;
   printf("\n");
   for (j = size; j >= 0; j--) {
        if (j == size) {

            /* This is one ugly thing, fix when more time */
            for (i = 0; i < 8; i++) {
                if (i == 0)
                    printf("\t%d", 8 - i - 1);
                else if (i == 1)
                    printf("\t %d", 8 - i - 1);
                else if (i == 2)
                    printf("\t  %d", 8 - i - 1);
                else if (i == 3)
                    printf("\t   %d", 8 - i - 1);
                else if (i == 4)
                    printf("\t    %d", 8 - i - 1);
                else if (i == 5)
                    printf("\t     %d", 8 - i - 1);
                else if (i == 6)
                    printf("\t      %d", 8 - i - 1);
                else if (i == 7)
                    printf("\t       %d", 8 - i - 1);

            }
            printf("\n");
        }
        else {

         for (i = 0; i < 8; i++) {
                  if (!(i))
                      printf(" ");
                if (j >= org_size)
                    printf(".");
                else
                    printf("%d", (data[j] >> (7 - i)) & 1);
              }
              if (j && j % 8 == 0 )
                  printf("\n");
        }
   }
	printf("\n");
}

