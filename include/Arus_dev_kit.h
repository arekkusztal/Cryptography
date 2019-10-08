/*
 * arus_dev_kit.h
 *
 *  Created on: Mar 5, 2018
 *      Author: arek67
 */

#ifndef ARUS_DEV_KIT_H_
#define ARUS_DEV_KIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define HEX_ME(arg) (arg - (arg < 58 ? 48 : 55))

void hex_dump(const char *def, uint8_t *data, uint16_t len,
		uint16_t br);

void bit_dump_b(uint8_t data);
void bit_dump_s(uint8_t *data, int size);

uint32_t lrotate32(uint32_t data, uint8_t shift);

#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)

#ifdef __cplusplus
}
#endif

#endif /* ARUS_DEV_KIT_H_ */
