SOURCES+=AES_ECB

all: $(SOURCES)

$(SOURCES): SETUP

.c:
	$(GCC) $(CFLAGS) $(LIB_OBJ)/*.o $< -o $(TEST_BUILD)/$@

.PHONY: SETUP	
SETUP:
	@if [ ! -d $(TEST_BUILD) ]; then \
		echo "== mkdir: create test/build"; \
		mkdir $(TEST_BUILD); \
	fi	
	
.PHONY: clean
clean:
	rm -f $(SOURCES)
