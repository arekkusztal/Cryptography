all: $(SOURCES-y)	

$(SOURCES-y): %.o : %.c
	$(S)gcc -c $(CFLAGS) $< -o $(LIB_OBJ)/$@ -g -O0
	$(S)echo cc: $@
	
.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(S)$(MAKE) -C $@ $(MFLAGS)