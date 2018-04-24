TESTS-y+=TEST_x690

all: $(TESTS-y)

#$(TESTS-y): SETUP
#.cpp:
#	g++ $(CFLAGS) $(LIB_OBJ)/*.o $< -o $(TEST_BUILD)/$@ -g -O0 -fpermissive -std=c++11
#	$(S) echo ld: $@

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