#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Arus_dev_kit.h>

#include <iostream>

#include <CRYPTO_LIB_common.h>
#include <Integer.hpp>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int random(uint8_t array, size_t size)
{
	int fd = open("/dev/random/", O_RDONLY);
	return 0;
}

int main(int argc, char *argv[])
{
	uint8_t random[8];
	int fd = open("/dev/random/", O_RDONLY);
	ssize_t _res = read(fd, random, sizeof(random));
	printf("\n RAND: %lx", *(uint64_t *)random);
	close(fd);
	return 0;
}
