SUBDIRS+=AES
SUBDIRS+=DES

all: $(SUBDIRS)	
	
.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@
	
.PHONY:
clean:
	rm -f build/*
