#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <Arus_dev_kit.h>
#include <CRYPTO_LIB_stream_cipher.h>

void LFSR_test()
{
	uint8_t a = 0x6;
	LFSR_4(a, 0x09);
}


int main()
{
	LFSR_test();
	return 0;
}
