all: $(SOURCES-y) $(SOURCESCPP-y)

$(SOURCES-y): %.o : %.c
	$(S)gcc -c $(CFLAGS) $< -o $(LIB_OBJ)/$@ -g -O0
	$(S)echo gcc: $@
	
$(SOURCESCPP-y): %.o : %.cpp
	$(S)g++ -c $(CFLAGS)  $< -o $(LIB_OBJ)/$@ -g -O0
	$(S)echo g++: $@

$(EXECPP-y): %.o : %.c
	$(S)g++ -c $(CFLAGS) -fpermissive $< -o $(LIB_OBJ)/$@ -g -O0
	$(S)echo g++: $@

$(TESTS-y): SETUP
.cpp:
	$(S)g++ $(CFLAGS) $(LIB_OBJ)/*.o $< -o $(TEST_BUILD)/$@ -g -O0 -fpermissive -std=c++11
	$(S) echo ld: $@
	
.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(S)$(MAKE) -C $@ $(MFLAGS)
