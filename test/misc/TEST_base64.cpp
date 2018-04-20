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
//static uint8_t rev_message[] = "VGVsbCBtZSwgTyBtdXNlLCBvZiB0aGF0IGluZ2VuaW91cyBoZXJvLCB3aG8gdHJhdmVsbGVkIGZhciBhbmQgd2lkZS4uLg==";

static uint8_t rev_message[] =
"MIIFiTCCA3GgAwIBAgIJAOOF1T0Apv6dMA0GCSqGSIb3DQEBCwUAMFsxCzAJBgNV"
"BAYTAlBMMRAwDgYDVQQIDAdMb2R6a2llMQ0wCwYDVQQHDARMb2R6MQ0wCwYDVQQK"
"DARBcnVzMQ0wCwYDVQQLDARBUlVTMQ0wCwYDVQQDDARBcnVzMB4XDTE4MDQyMDA1"
"MzYzNFoXDTE5MDQyMDA1MzYzNFowWzELMAkGA1UEBhMCUEwxEDAOBgNVBAgMB0xv"
"ZHpraWUxDTALBgNVBAcMBExvZHoxDTALBgNVBAoMBEFydXMxDTALBgNVBAsMBEFS"
"VVMxDTALBgNVBAMMBEFydXMwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoIC"
"AQCutFBuB73XtWmjWuM/NkG0XVcV+V35zs6qx462LDSUyJ2cOh6MeKxYggrTCGWk"
"jWP41mr61UR1qn7EeA1SjqZWCxh3Bo9v1lm7C1XbGmDBy5WHRoa0N/ttJQBalCwN"
"2pWg71ZeKjK8RhTNmc9eTIvBQbIaxgQTlzbN8NwRlM+r1y6HWutW4xI/tmfjlv0G"
"Oc7TUY+1PR51eTIfguhIgjXvTgzEIFMdjYUo5vyMwSP+acekaZCtyuGDLpr0OZRG"
"ZcbJK2gFvb2rERe9jTDwWUBkUcvAV6D5tn+8CLAbdCFoqayxhMalqJBqvF/XfYBi"
"LA20Ja8YwhFvHvRpsMdAvqHH8QWYCffTxQK6FhJe4aF7EDktbfHKvI8aUq7cVsm5"
"4KNlJbZ98BJiyL/Zir2dDp+lCYRthk0Oclpf2xOx8Czle41bcQ6WsrGgDYSVw35t"
"riSVG/UESWbe7496vQeSsAJbmQEK7qohHbQF3mvg+pFQeM+N+EF6jVGKjfE94Yo5"
"YIv7ys9YasN+CC9jxXPd5+kM3+HF5KtkJCpt/KV184L5y3DLjHmtxzCPi1mca/4M"
"RE9FPxGfgNYlfNGiXF5F9sfdv7KjGnZFiYyK9yIwsGByHfeX7osW2vsgq9Rhw9IU"
"bxd6DNsMVD3AP1OhhtQEUtg+yRXaRU8TRmWiKHLu6QRvNQIDAQABo1AwTjAdBgNV"
"HQ4EFgQUdqRYMrQF7Mbiqv1p22Q2qcTxVTYwHwYDVR0jBBgwFoAUdqRYMrQF7Mbi"
"qv1p22Q2qcTxVTYwDAYDVR0TBAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAgEAhlLV"
"KPOKMIpzmD2/o5pxoQup5rAEoaIbDH4WCaszJ8mEaqnSwFFGGtnrWCq0lcEwUbTY"
"REaX6NPDXxchayM2GJ9x9AeJTyfDflVEcfTpT79492WvvlS5TmT0C1DhRS+4fGWX"
"tuuNkT8+Iyi0UvU4zYjQGPtO/bxdJAlxY7LV6bgR5a/YZSf8WJvclMdocKjjPgZ+"
"xfsKEJ+k5J97BhGiqWtAGkUqqmJMTwXjzgdtFYsX4PaaIQDXexXoMOmB5atZTufy"
"05HuBCmS4DQ/PB/BThI4bvNahy6CBPnjyeRbm7UFwxoo1ha0u/sf2iDOauCbrQIG"
"+rRDr1a/qUBFD0QNZaFD7gR03ap+06wuKMhlR88JOoYP/SLyWS29rQkD/0d59QbL"
"Wv8+5hJRoP4/HDDz9TBxJXkGm7PrbX6Y1lnh0kNuH2aljec1PXJobBjmYFfxwZj9"
"g5YXy8Zc+t7I717WRvD+VllMohgqLqG6/GPQXZB/N8q++VMvkp2BCt4/jSHlZ2Ky"
"90pbkhtROQb7/h9cj3ebIErpyN9Idoq04BcgSwEj4JRFLy6zyT5bOnxP5pju4NdL"
"NhwjsCI+1lY5YCdfVjhrkX+sbe9B1slrd4kzkAXW88fQGTyo3jgh9KwRm9SMAuMe"
"lFStERq2QLmyrGo+cB9jYFxmNQ6LDjjxf6Bs3hM=";


int read_cert()
{
	FILE *f = fopen("cert.der", "rb");
	if (f == NULL) {
		perror("f: ");
		return 1;
	}

	long size;
	size_t result;
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	rewind(f);

	printf("\n f size = %d", (int)size);
	uint8_t *buffer = (uint8_t *)malloc(size);
	result = fread(buffer, 1, size, f);

	hex_dump("cert.der", buffer, size, 16);

	free(buffer);
	fclose(f);
	return 0;
}

int main()
{
	uint8_t *msg;
	return read_cert();
	//msg = strtbase64(message, sizeof(message) - 1);
	msg = base64_to_str(rev_message, sizeof(rev_message) - 1);

	printf("\nout:\n%s\n", msg);
	return 0;
}
