#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <CRYPTO_LIB_common.h>


//static uint8_t message[] = "abcde";
//static uint8_t rev_message[] = "YWJjZGU=";
//static uint8_t message[] = "1683 Vienna.";
static uint8_t message[] = "Tell me, O muse, of that ingenious hero, who travelled far and wide...";
static uint8_t rev_message[] = "VGVsbCBtZSwgTyBtdXNlLCBvZiB0aGF0IGluZ2VuaW91cyBoZXJvLCB3aG8gdHJhdmVsbGVkIGZhciBhbmQgd2lkZS4uLg==";

int main()
{
	uint8_t *msg;

	//msg = strtbase64(message, sizeof(message) - 1);
	msg = base64_to_str(rev_message, sizeof(rev_message) - 1);

	printf("\nout:\n%s\n", msg);
	return 0;
}
