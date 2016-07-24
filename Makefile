CFLAGS=-I$(PWD)/include
export CFLAGS

all:
	$(MAKE) -C crypto_algs
.PHONY:
clean:
	$(MAKE) -C crypto_algs clean
	
