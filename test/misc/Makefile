TESTS-y+=TEST_base64

all: $(TESTS-y)

.PHONY: SETUP	
SETUP:
	@if [ ! -d $(TEST_BUILD) ]; then \
		echo "md: create test/build"; \
		mkdir $(TEST_BUILD); \
	fi	
	
.PHONY: clean
clean:
	rm -f $(SOURCES)


include $(CRYPTO_LIB)/build.src.mk
