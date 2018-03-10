SOURCES+=new

all: $(SOURCES)

$(SOURCES): SETUP

.c:
	$(S)$(GCC) $(CFLAGS) $(LIB_OBJ)/*.o $< -o $(TEST_BUILD)/TEST_$@ -g -O0
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
