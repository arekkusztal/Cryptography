CFLAGS=-I$(PWD)/include
BUILD=$(CRYPTO_LIB)/build
LIB_OBJ=$(BUILD)/lib_obj
MFLAGS=--no-print-directory
LIB-X=lib

DIRS+=crypto_algs
GCC=gcc

LIB_OBJ_FILES = $(wildcard $(LIB_OBJ)/*.o)

export CFLAGS
export LIB_OBJ
all: $(LIB-X)

$(LIB-X): $(DIRS)
	$(GCC) -o $(BUILD)/$@ $(LIB_OBJ_FILES) main.c
	
.PHONY: $(DIRS)
$(DIRS): SETUP
	$(MAKE) -C $@ $(MFLAGS)
	
.PHONY: SETUP
SETUP:
	@if [ ! -d $(BUILD) ]; then \
		echo "== mkdir: creating build directory"; \
		mkdir $(BUILD); \
		mkdir $(LIB_OBJ); \
	fi

.PHONY:
#clean: $(LIB_OBJ)
#	rm -f $^/*.o
clean:
	rm build/ -rf
	
	
