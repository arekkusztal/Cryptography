#SOURCES+=AES_ECB
SOURCES+=AES_CBC

all: $(SOURCES)

$(SOURCES): SETUP

.c:
	$(GCC) $(CFLAGS) $(LIB_OBJ)/*.o $< -o $(TEST_BUILD)/$@ -g -O0

.PHONY: SETUP	
SETUP:
	@if [ ! -d $(TEST_BUILD) ]; then \
		echo "== mkdir: create test/build"; \
		mkdir $(TEST_BUILD); \
	fi	
	
.PHONY: clean
clean:
	rm -f $(SOURCES)
