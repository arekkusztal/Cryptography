SUBDIRS-y+=symmetric
SUBDIRS-y+=asymmetric
SUBDIRS-y+=stream

all: $(SUBDIRS-y)	
	
.PHONY:
clean:
	rm -f build/*

include $(CRYPTO_LIB)/build.src.mk 
