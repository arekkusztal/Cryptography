SUBDIRS+=AES
SUBDIRS+=DES
SUBDIRS+=Twofish

all: $(SUBDIRS)	
	
.PHONY:
clean:
	rm -f build/*

include $(CRYPTO_LIB)/build.src.mk 
