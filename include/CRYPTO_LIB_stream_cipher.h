#ifndef CRYPTO_LIB_STREAM_CIPHER_H
#define CRYPTO_LIB_STREAM_CIPHER_H

#include <stdio.h>
#include <stdint.h>

uint8_t LFSR_8(uint8_t arg, uint8_t mask);
uint8_t LFSR_4(uint8_t arg, uint8_t mask);

#endif
