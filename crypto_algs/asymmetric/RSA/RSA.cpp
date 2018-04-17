#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Arus_dev_kit.h>

#include <CRYPTO_LIB_common.h>
#include <CRYPTO_LIB_RSA.hpp>
#include <Integer.hpp>

bool check_if_coprime(integer a, integer w)
{
	integer i;
	for (i = 2; i < a; i++)
		if ( !(a % i) && !(w % i) )
			return false;

	return true;
}

integer get_modinv(integer a, integer n)
{
	/*
	 * Prequisites, coprime etc...
	 */

	integer i;
	for (i = 2; i < ~((uint64_t)0); i++)
		if ( (a * i) % n == 1)
			return i;
	return 0;
}

integer RSA_choose_e(integer phi)
{
	return 0;
}
