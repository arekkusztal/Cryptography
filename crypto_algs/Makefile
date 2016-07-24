all:
	$(MAKE) -C AES/ECB/c
	$(MAKE) -C AES/CBC/c
	$(MAKE) -C AES/OFB/c
	$(MAKE) -C AES/CFB/c
	$(MAKE) -C AES/CTR/c
	$(MAKE) -C AES/GCM/c
	$(MAKE) -C AES/AES
	gcc -o build/ecb AES/ECB/c/AES_ECB.o AES/AES/AES.o
	gcc -o build/cbc AES/CBC/c/AES_CBC.o AES/AES/AES.o
	gcc -o build/ofb AES/OFB/c/AES_OFB.o AES/AES/AES.o
	gcc -o build/cfb AES/CFB/c/AES_CFB.o AES/AES/AES.o
	gcc -o build/ctr AES/CTR/c/AES_CTR.o AES/AES/AES.o
	gcc -o build/gcm AES/GCM/c/AES_GCM.o AES/AES/AES.o
	
.PHONY:
clean:
	rm -f build/*
	$(MAKE) -C AES/ECB/c clean
	$(MAKE) -C AES/CBC/c clean
	$(MAKE) -C AES/OFB/c clean
	$(MAKE) -C AES/CFB/c clean
	$(MAKE) -C AES/CTR/c clean
	$(MAKE) -C AES/GCM/c clean
	$(MAKE) -C AES/AES clean
