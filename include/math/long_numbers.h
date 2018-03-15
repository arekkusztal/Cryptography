/*
 * long_numbers.h
 *
 *  Created on: Mar 5, 2018
 *      Author: arek67
 */

#ifndef LONG_NUMBERS_H_
#define LONG_NUMBERS_H_

#include <stdint.h>
#include <Arus_dev_kit.h>

typedef struct Integer {
	uint8_t *data;
	uint16_t size;
} integer;

integer*
set_integer_b16(uint8_t *array);

int
set_integer_128_b16(uint8_t *array, uint8_t *placeholder, int len);

int 
sub_integer_128(uint8_t *A, uint8_t *B, uint8_t *R);

int
add_integer_128(uint8_t *A, uint8_t *B, uint8_t *R);

integer*
set_integer(uint8_t *array);

integer*
add_integer(integer *A, integer *B);

integer*
lshift(integer *A);

integer*
mult(integer *A, integer *B);

#endif /* LONG_NUMBERS_H_ */
