INCLUDE=-I$(PWD)/include -I$(PWD)/include/math -I$(PWD)/include/x.509 -I$(PWD)/include/ASN.1
CFLAGS=$(INCLUDE) -Dx86
BUILD=$(CRYPTO_LIB)/build
LIB_OBJ=$(BUILD)/lib_obj
MFLAGS=--no-print-directory
TEST_BUILD=$(CRYPTO_LIB)/test/build
LIB-X=lib
S=@

standard=y
x86=n

DIRS+=crypto_algs
DIRS+=crypto_modes
DIRS+=math
DIRS+=common
DIRS+=misc
DIRS+=hash
DIRS+=x.509
DIRS+=ASN.1
DIRS+=test

GCC=gcc
GPP=g++

LIB_OBJ_FILES = $(wildcard $(LIB_OBJ)/*.o)

export S
export CFLAGS
export LIB_OBJ
export GCC
export TEST_BUILD
export standard
export x86

all: $(LIB-X)

$(LIB-X): $(DIRS)
	$(S)$(GPP) -o $(BUILD)/$@ $(LIB_OBJ_FILES) main.c
	$(S)echo ld: $@
	
.PHONY: $(DIRS)
$(DIRS): SETUP
	$(S)$(MAKE) -C $@ $(MFLAGS)
	
.PHONY: SETUP
SETUP: CHECK_ENV
	@if [ ! -d $(BUILD) ]; then \
		echo "== mkdir: creating build directory"; \
		mkdir $(BUILD); \
		mkdir $(LIB_OBJ); \
	fi

.PHONY: CHECK_ENV
CHECK_ENV:
ifndef CRYPTO_LIB
	$(error  CRYPTO_LIB not defined, should be defined with working directory)
endif	

.PHONY:
#clean: $(LIB_OBJ)
#	rm -f $^/*.o
clean: $(BUILD) $(TEST_BUILD)

.PHONY: $(BUILD) $(TEST_BUILD)
$(BUILD) $(TEST_BUILD):
	rm -rf $@
	@echo "== rm:" $@
	
include build.src.mk	
	
