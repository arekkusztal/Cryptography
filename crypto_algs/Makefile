SUBDIRS=AES/ECB/c
SUBDIRS+=AES/CBC/c
SUBDIRS+=AES/OFB/c
SUBDIRS+=AES/CFB/c
SUBDIRS+=AES/CTR/c
SUBDIRS+=AES/GCM/c
SUBDIRS+=AES/AES

all: $(SUBDIRS)
	@if [ ! -d build ]; then \
		echo " -- INFO: build directory does not exists"; \
		mkdir build; \
	fi
	@gcc -o build/ecb AES/ECB/c/AES_ECB.o AES/AES/AES.o
	@gcc -o build/cbc AES/CBC/c/AES_CBC.o AES/AES/AES.o
	@gcc -o build/ofb AES/OFB/c/AES_OFB.o AES/AES/AES.o
	@gcc -o build/cfb AES/CFB/c/AES_CFB.o AES/AES/AES.o
	@gcc -o build/ctr AES/CTR/c/AES_CTR.o AES/AES/AES.o
	@gcc -o build/gcm AES/GCM/c/AES_GCM.o AES/AES/AES.o
	
	
	
.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@
	
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
