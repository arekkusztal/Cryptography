#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <long_numbers.hpp>

#include <CRYPTO_LIB_common.h>
#include <Arus_dev_kit.h>


template class Integer<16>;
template class Integer<32>;
template class Integer<128>;
template class Integer<256>;
template class Integer<512>;
template class Integer<4096>;
template class Integer<8192>;
