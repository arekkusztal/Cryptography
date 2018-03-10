/*
 * arus_dev_kit.h
 *
 *  Created on: Mar 5, 2018
 *      Author: arek67
 */

#ifndef ARUS_DEV_KIT_H_
#define ARUS_DEV_KIT_H_

#define HEX_ME(arg) (arg - (arg < 58 ? 48 : 55))

void hex_dump(const char *def, uint8_t *data, uint16_t len,
		uint16_t br);

void bit_dump(uint8_t data);

#endif /* ARUS_DEV_KIT_H_ */
