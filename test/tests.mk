##################
#    libsutil    #
#                #
#  sudo200 and   #
#  contributors  #
#                #
#  Tests config  #
#      file      #
##################

TEST_INCLUDE=-I$(INCLUDE) -I./libs/sunit/include

TEST_FILE=$(TEST_DIR)/file_test.c
TEST_MSTRING=$(TEST_DIR)/mstring_test.c
TEST_ARRAYLIST=$(TEST_DIR)/arraylist_test.c
TEST_LINKEDLIST=$(TEST_DIR)/linkedlist_test.c
TEST_QUEUE=$(TEST_DIR)/queue_test.c
TEST_UTIL=$(TEST_DIR)/util_test.c
TEST_ARGPARSER=$(TEST_DIR)/argparser_test.c
TEST_LOGGER=$(TEST_DIR)/logger_test.c
TEST_STACK=$(TEST_DIR)/stack_test.c

test_file: all
	$(CC) -o$(OUT)/test_file $(TEST_INCLUDE) $(TEST_FILE) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) ./$(OUT)/test_file

test_mstring: all
	$(CC) -o$(OUT)/test_mstring $(TEST_INCLUDE) $(TEST_MSTRING) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) ./$(OUT)/test_mstring

test_arraylist: all
	$(CC) -o$(OUT)/test_arraylist $(TEST_INCLUDE) $(TEST_ARRAYLIST) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) ./$(OUT)/test_arraylist

test_linkedlist: all
	$(CC) -o$(OUT)/test_linkedlist $(TEST_INCLUDE) $(TEST_LINKEDLIST) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) ./$(OUT)/test_linkedlist

test_queue: all
	$(CC) -o$(OUT)/test_queue $(TEST_INCLUDE) $(TEST_QUEUE) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) ./$(OUT)/test_queue

test_util: all
	$(CC) -o$(OUT)/test_util $(TEST_INCLUDE) $(TEST_UTIL) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) ./$(OUT)/test_util

test_argparser: all
	$(CC) -o$(OUT)/test_argparser $(TEST_INCLUDE) $(TEST_ARGPARSER) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) ./$(OUT)/test_argparser

test_logger: all
	$(CC) -o$(OUT)/test_logger $(TEST_INCLUDE) $(TEST_ARGPARSER) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) ./$(OUT)/test_logger

test_stack: all
	$(CC) -o$(OUT)/test_stack $(TEST_INCLUDE) $(TEST_STACK) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) ./$(OUT)/test_stack

test: test_file test_mstring test_arraylist test_queue test_util test_argparser test_logger test_stack

.PHONY: test test_file test_mstring test_arraylist test_linkedlist test_queue test_util test_argparser test_logger test_stack

