#include <Integer.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include <CRYPTO_LIB_common.h>
#include <Arus_dev_kit.h>

#define DEBUG_MW

int MW_COUNT;

template <uint16_t len, SIGNEDNESS sign>
DIV_RESULT<len, sign> Integer<len, sign>::metoda_wielkanocna(const Integer<len, sign>& B)
{
	int __local_count;
	//printf("\n metoda_wielkanocna ----------");
	__local_count = MW_COUNT++;
	int i;
    DIV_RESULT<len, sign> res = { };

    Integer<len, sign> __sub_1 = "1";
    Integer<len, sign> __temp;
    DIV_RESULT<len, sign> __temp_res[32] = { };
    uint16_t __len_to_shift, __bits_to_shift[32];
    if (*this < B) {
        res.ret = "0";
        res.mod = *this;

       // res.ret.print_s("ret =F");
       // res.mod.print_s("mod =F");
        return res;
    } else if (*this == B) {
    	res.ret = "1";
		res.mod = "0";
		return res;
    } else if (this->__len_in_bits == B.__len_in_bits) {
    	res.ret = "1";
    	res.mod = *this - B;
    	return res;
    }

    int __iteration__ = 0, __bits_added = 0, __mod_ladder_cout = 0;
    while (*this > B) {
        __temp = B;
        __len_to_shift = this->__len_in_bits - __temp.__len_in_bits;
        __temp <<= __len_to_shift;

        if (*this > __temp) {
        	*this = *this - __temp;
        }
        else if (*this < __temp) {
            uint16_t __pos = this->__len_in_bits - 1;
            Integer<len, sign> __temp_internal;
            while (*this < __temp) {
                if ( (!(this->__data[__pos >> 3] >> (__pos & 0x7) & 1))
                     && (__temp.__data[__pos >> 3] >> (__pos & 0x7) & 1))
                {
                    *this |= __pos;
                    __temp_internal |= __pos;
                }
                __pos--;

            }
            __temp_res[__mod_ladder_cout] = __temp_internal.metoda_wielkanocna(B);
            __temp_internal = __temp_internal >> 128;
            __mod_ladder_cout++;
            *this = *this - __temp;
        } else if (*this == __temp) {
        	*this = "0";
        }


        res.ret |= __len_to_shift;

    }

    for (i = 0; i < __mod_ladder_cout; i++) {
      if (*this < __temp_res[i].mod) {
    	    *this = *this + B;
    		res.ret = res.ret - __sub_1;
    	}
		*this = *this - __temp_res[i].mod;
		res.ret = res.ret - __temp_res[i].ret;
    }

    res.mod = *this;
   // res.ret.print_s("ret =");
   // res.mod.print_s("mod =");

    return res;
}
