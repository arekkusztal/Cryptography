SOURCES+=TEST_long_numbers

all: $(SOURCES)

$(SOURCES): SETUP

.cpp:
	g++ $(CFLAGS) $(LIB_OBJ)/*.o $< -o $(TEST_BUILD)/$@ -g -O0 -fpermissive -std=c++11
	$(S) echo ld: $@

.PHONY: SETUP	
SETUP:
	@if [ ! -d $(TEST_BUILD) ]; then \
		echo "md: create test/build"; \
		mkdir $(TEST_BUILD); \
	fi	
	
.PHONY: clean
clean:
	rm -f $(SOURCES)
