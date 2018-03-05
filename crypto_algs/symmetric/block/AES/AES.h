#include <stdint.h>

#ifndef AES_H_
#define AES_H_

#define hex_dump_2_(a,b,c,d) hex_dump(a,b,c,d)
#define hex_dump_2(a,b,c,d)

/* Multiplication over golis field characteristic 2 with 256 elements */
uint8_t GMUL2[256];
uint8_t GMUL3[256];
uint8_t GMUL9[256];
uint8_t GMUL11[256];
uint8_t GMUL13[256];
uint8_t GMUL14[256];

uint8_t rcon[256];
uint8_t s_box[256];
uint8_t s_box_inv[256];

#endif /* AES_H_ */
