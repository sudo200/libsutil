##################
#    libsutil    #
#                #
#  sudo200 and   #
#  contributors  #
#                #
#  Tests config  #
#      file      #
##################

TEST_STRSPL=$(TEST_DIR)/strspl_test.c
TEST_FILE=$(TEST_DIR)/file_test.c
TEST_MSTRING=$(TEST_DIR)/mstring_test.c
TEST_ARRAYLIST=$(TEST_DIR)/arraylist_test.c

test_strspl: all
	$(CC) -o$(OUT)/test_strspl -I$(INCLUDE) $(TEST_STRSPL) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) $(UNITTEST) ./$(OUT)/test_strspl

test_file: all
	$(CC) -o$(OUT)/test_file -I$(INCLUDE) $(TEST_FILE) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) $(UNITTEST) ./$(OUT)/test_file

test_mstring: all
	$(CC) -o$(OUT)/test_mstring -I$(INCLUDE) $(TEST_MSTRING) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) $(UNITTEST) ./$(OUT)/test_mstring

test_arraylist: all
	$(CC) -o$(OUT)/test_arraylist -I$(INCLUDE) $(TEST_ARRAYLIST) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) $(UNITTEST) ./$(OUT)/test_arraylist

test: test_strspl test_file test_mstring test_arraylist

.PHONY: test test_strspl test_file test_mstring test_arraylist

