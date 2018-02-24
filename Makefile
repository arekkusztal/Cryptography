CFLAGS=-I$(PWD)/include
export CFLAGS

all:
	$(MAKE) -C crypto_algs --no-print-directory
.PHONY:
clean:
	$(MAKE) -C crypto_algs clean
	
