#include <Integer.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include <CRYPTO_LIB_common.h>
#include <Arus_dev_kit.h>

/*
 * ********** Logical operators  **********
*/

template <uint16_t len>
bool Integer<len>::operator>(const Integer<len>& B)
{
    int i;
    if (this->__len_in_bits > B.__len_in_bits)
        return true;
    else if (this->__len_in_bits < B.__len_in_bits)
        return false;
    else {
        i = this->__len;
        while (i >= 0) {
            if (this->__data[i] > B.__data[i])
                return true;
            else if (this->__data[i] < B.__data[i])
                return false;
            i--;
        }

    }
    return false;
}

template <uint16_t len>
bool Integer<len>::operator<(const Integer<len>& B)
{
    int i;
    if (this->__len_in_bits < B.__len_in_bits)
        return true;
    else if (this->__len_in_bits > B.__len_in_bits)
        return false;
    else {
        i = this->__len - 1;
        while (i >= 0) {
            if (this->__data[i] < B.__data[i])
                return true;
            else if (this->__data[i] > B.__data[i])
                return false;
            i--;
        }

    }
    return false;
}

template <uint16_t len>
bool Integer<len>::operator==(Integer<len> A)
{
	int i;
	if (this->__len_in_bits != A.__len_in_bits)
		return false;

	if (!memcmp(this->__data, A.__data, this->__len))
		return true;
	else
		return false;
}
