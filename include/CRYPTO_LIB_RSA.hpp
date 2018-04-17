
#ifndef CRYPTO_LIB_RSA_HPP_
#define CRYPTO_LIB_RSA_HPP_

#include <stdint.h>
#include "Arus_dev_kit.h"

/* Long number should be... */
typedef uint64_t integer;

#define RSA_Euler_Totient(p, q) \
	(p - 1) * (q - 1);

integer RSA_choose_e(integer phi);
bool check_if_coprime(integer a, integer w);
integer get_modinv(integer a, integer n);

#endif
