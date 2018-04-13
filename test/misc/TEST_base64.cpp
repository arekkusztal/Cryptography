#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <CRYPTO_LIB_common.h>

//static uint8_t message[] = "1683 Vienna.";
static uint8_t message[] = "Tell me, O muse, of that ingenious hero, who travelled far and wide...";

int main()
{
	uint8_t *msg;

	msg = strtbase64(message, sizeof(message)-1);

	printf("\nout:\n%s\n", msg);
	return 0;
}
