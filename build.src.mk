all: $(SOURCES-y) $(SOURCESCPP-y)

$(SOURCES-y): %.o : %.c
	$(S)gcc -c $(CFLAGS) $< -o $(LIB_OBJ)/$@ -g -O0
	$(S)echo cc: $@
	
$(SOURCESCPP-y): %.o : %.c
	$(S)g++ -c $(CFLAGS) -fpermissive $< -o $(LIB_OBJ)/$@ -g -O0
	$(S)echo cc: $@
	
.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(S)$(MAKE) -C $@ $(MFLAGS)