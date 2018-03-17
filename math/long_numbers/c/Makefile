SOURCESCPP-y+=long_numbers.o
#SOURCESCPP-y+=long_mumbers_arithmetic.o
#SOURCESCPP-y+=karatsuba.o
#SOURCESCPP-y+=montgomery_reduction.o

$(SOURCESCPP-y): %.o : %.cpp
	g++ -c $(CFLAGS) -fpermissive $< -o $(LIB_OBJ)/$@ -g -O0
	$(S)echo g++: $@

#include $(CRYPTO_LIB)/build.src.mk
