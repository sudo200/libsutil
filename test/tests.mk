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

test: $(OUT)/test_file \
	$(OUT)/test_mstring \
	$(OUT)/test_arraylist \
	$(OUT)/test_queue \
	$(OUT)/test_util \
	$(OUT)/test_argparser \
	$(OUT)/test_logger \
	$(OUT)/test_stack \
	
	@echo 'ALL TESTS PASSED!'

$(OUT)/test_%: all
	$(CC) -o$@ $(TEST_INCLUDE) $(TEST_DIR)/$(patsubst $(OUT)/test_%,%,$@)_test.c $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) ./$@

.PHONY: test \

