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
TEST_LINKEDLIST=$(TEST_DIR)/linkedlist_test.c
TEST_QUEUE=$(TEST_DIR)/queue_test.c
TEST_UTIL=$(TEST_DIR)/util_test.c

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

test_linkedlist: all
	$(CC) -o$(OUT)/test_linkedlist -I$(INCLUDE) $(TEST_LINKEDLIST) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) $(UNITTEST) ./$(OUT)/test_linkedlist

test_queue: all
	$(CC) -o$(OUT)/test_queue -I$(INCLUDE) $(TEST_QUEUE) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) $(UNITTEST) ./$(OUT)/test_queue

test_util: all
	$(CC) -o$(OUT)/test_util -I$(INCLUDE) $(TEST_UTIL) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) $(UNITTEST) ./$(OUT)/test_util

test: test_strspl test_file test_mstring test_arraylist test_queue test_util

.PHONY: test test_strspl test_file test_mstring test_arraylist test_linkedlist test_queue test_util

