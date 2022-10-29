##################
#    libsutil    #
#                #
#  sudo200 and   #
#  contributors  #
#                #
#  Tests config  #
#      file      #
##################

TEST_FILE=$(TEST_DIR)/file_test.c
TEST_MSTRING=$(TEST_DIR)/mstring_test.c
TEST_ARRAYLIST=$(TEST_DIR)/arraylist_test.c
TEST_LINKEDLIST=$(TEST_DIR)/linkedlist_test.c
TEST_QUEUE=$(TEST_DIR)/queue_test.c
TEST_UTIL=$(TEST_DIR)/util_test.c
TEST_DSTRING=$(TEST_DIR)/dstring_test.c
TEST_ARGPARSER=$(TEST_DIR)/argparser_test.c

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

test_dstring: all
	$(CC) -o$(OUT)/test_dstring -I$(INCLUDE) $(TEST_DSTRING) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) $(UNITTEST) ./$(OUT)/test_dstring

test_argparser: all
	$(CC) -o$(OUT)/test_argparser -I$(INCLUDE) $(TEST_ARGPARSER) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) $(UNITTEST) ./$(OUT)/test_argparser

test: test_file test_mstring test_arraylist test_queue test_util test_dstring test_argparser

.PHONY: test test_file test_mstring test_arraylist test_linkedlist test_queue test_util test_dstring test_argparser

