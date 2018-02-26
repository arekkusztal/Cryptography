all: $(SOURCES-y)	

$(SOURCES-y): %.o : %.c
	gcc -c $(CFLAGS) $< -o $(LIB_OBJ)/$@