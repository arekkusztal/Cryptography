SOURCESCPP-y+=Integer.o
SOURCESCPP-y+=Integer_arithmetic.o
SOURCESCPP-y+=Integer_binary_ops.o
SOURCESCPP-y+=Integer_logical.o
SOURCESCPP-y+=Integer_misc.o
SOURCESCPP-y+=Metoda_wielkanocna.o
SOURCESCPP-y+=Karatsuba.o

#$(SOURCESCPP-y): %.o : %.cpp
#	g++ -c $(CFLAGS)  $< -o $(LIB_OBJ)/$@ -g -O0
#	$(S)echo g++: $@

include $(CRYPTO_LIB)/build.src.mk
