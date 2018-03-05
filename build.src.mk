all: $(SOURCES-y)	

$(SOURCES-y): %.o : %.c
	@gcc -c $(CFLAGS) $< -o $(LIB_OBJ)/$@ -g -O0
	@echo cc: $@
	
.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(S)$(MAKE) -C $@ $(MFLAGS)