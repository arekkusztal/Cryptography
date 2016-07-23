

all:
	$(MAKE) -C AES/ECB/c
	$(MAKE) -C AES/CBC/c
	$(MAKE) -C AES/AES
	gcc -o build/ecb AES/ECB/c/AES_ECB.o AES/AES/AES.o
	gcc -o build/cbc AES/CBC/c/AES_CBC.o AES/AES/AES.o
	
#	$(cd) AES/ECB/c;
#	touch abcd;
#	$(MAKE) -f Makefile