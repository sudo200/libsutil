INCLUDE="./include"
SRC="./src"
OUT="./out"
OBJS=$(OUT)/*.o
LIBNAME=sutil
CFLAGS=-pedantic -Wall -g -fPIC

TEST_DIR=./test
TEST_STRSPL=$(TEST_DIR)/strspl_test.c

OBJCPY=objcopy


all: strspl.o out/

	$(CC) -shared -o$(OUT)/lib$(LIBNAME).so $(OBJS)
	chmod -x $(OUT)/lib$(LIBNAME).so
	$(OBJCPY) --only-keep-debug $(OUT)/lib$(LIBNAME).so $(OUT)/lib$(LIBNAME).so.dbg
	chmod -x $(OUT)/lib$(LIBNAME).so.dbg
	$(OBJCPY) --strip-unneeded $(OUT)/lib$(LIBNAME).so
	$(OBJCPY) --add-gnu-debuglink=$(OUT)/lib$(LIBNAME).so.dbg $(OUT)/lib$(LIBNAME).so

strspl.o: out/

	$(CC) -c -I$(INCLUDE) -o$(OUT)/strspl.o $(SRC)/strspl.c

out/:

	mkdir -p $(OUT)

test_strspl: all
	$(CC) -o$(OUT)/test_strspl -I$(INCLUDE) $(TEST_STRSPL) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) ./$(OUT)/test_strspl

clean:
	$(RM) -r $(OUT)

.PHONY: test test_strspl clean all

