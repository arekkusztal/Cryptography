#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <Arus_dev_kit.h>
#include <CRYPTO_LIB_stream_cipher.h>
#include <CRYPTO_LIB_hash.h>

void LFSR_test()
{
	uint8_t a = 0x6;
	LFSR_4(a, 0x09);
}

void lrotate_test()
{
	uint32_t b = 0xC00000A1;
	bit_dump_s((uint8_t *)&b, 4);
	b = lrotate32(b , 30);
	bit_dump_s((uint8_t *)&b, 4);
}

char string[16];
uint8_t ret[20];

int main()
{
	//lrotate_test();
	hex_dump("before", ret, 20, 16);
	SHA1(ret, string, 16);
	hex_dump("after", ret, 20, 16);
	return 0;
}
