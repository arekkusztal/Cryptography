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

template <uint16_t len, SIGNEDNESS sign>
bool Integer<len, sign>::operator>(const Integer<len, sign>& B)
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

template <uint16_t len, SIGNEDNESS sign>
bool Integer<len, sign>::operator<(const Integer<len, sign>& B)
{
    int i;
    bool __unsigned;
    bool ret;

    __unsigned = true;
    ret = false;

    if (sign == SIGNED) {
    	if ( (this->__data[this->__len - 1] & 0x80) && (! (B.__data[this->__len - 1] & 0x80) )) {
    		return true;
    	}
    	else if ( !(this->__data[this->__len - 1] & 0x80) && ((B.__data[this->__len - 1] & 0x80) )) {
    		return false;
    	}
    	else if ( (this->__data[this->__len - 1] & 0x80) &&  (B.__data[this->__len - 1] & 0x80) ) {
    		__unsigned = false;
    	}
    } else {
		if (this->__len_in_bits < B.__len_in_bits)
			return true;
		else if (this->__len_in_bits > B.__len_in_bits)
			return false;
    }

    if (this->__len_in_bits < B.__len_in_bits) {
        ret = true;
        goto __return;
    }
    else if (this->__len_in_bits > B.__len_in_bits) {
        ret = false;
        goto __return;
    }
    else {
        i = this->__len - 1;
        while (i >= 0) {
            if (this->__data[i] < B.__data[i]) {
                ret = true;
                goto __return;
            }
            else if (this->__data[i] > B.__data[i]) {
                ret = false;
                goto __return;
            }
            i--;
        }
    }

__return:
    return ret ;//& __unsigned;
}

template <uint16_t len, SIGNEDNESS sign>
bool Integer<len, sign>::operator==(Integer<len, sign> A)
{
	int i;
	if (this->__len_in_bits != A.__len_in_bits)
		return false;

	if (!memcmp(this->__data, A.__data, this->__len))
		return true;
	else
		return false;
}
