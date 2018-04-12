SUBDIRS-y+=AES
SUBDIRS-y+=DES
SUBDIRS-y+=Twofish

all: $(SUBDIRS-y)	
	
.PHONY:
clean:
	rm -f build/*

include $(CRYPTO_LIB)/build.src.mk 
