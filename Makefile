###################
#    libsutils    #
#                 #
#		sudo200 and   #
#	 contributors   #
#                 #
#	 Main makefile  #
#                 #
###################

include config.mk


$(OUT)/lib$(LIBNAME).so: $(OUT) $(OBJ)/strspl.o
	$(CC) -shared -o$(OUT)/lib$(LIBNAME).so $(OBJ)/*.o
	chmod -x $(OUT)/lib$(LIBNAME).so	
	$(OBJCPY) --only-keep-debug $(OUT)/lib$(LIBNAME).so $(OUT)/lib$(LIBNAME).so.dbg
	chmod -x $(OUT)/lib$(LIBNAME).so.dbg
	$(OBJCPY) --strip-unneeded $(OUT)/lib$(LIBNAME).so
	$(OBJCPY) --add-gnu-debuglink=$(OUT)/lib$(LIBNAME).so.dbg $(OUT)/lib$(LIBNAME).so

$(OBJ)/strspl.o: $(OBJ) $(SRC)/strspl.c
	$(CC) -c -I$(INCLUDE) -o$(OBJ)/strspl.o $(SRC)/strspl.c

$(OUT):
	mkdir -p $(OUT)

$(OBJ):
	mkdir -p $(OBJ)

all: $(OUT)/lib$(LIBNAME).so

test_strspl: all
	$(CC) -o$(OUT)/test_strspl -I$(INCLUDE) $(TEST_STRSPL) $(CFLAGS) -L$(OUT) -l$(LIBNAME)
	LD_LIBRARY_PATH=$(OUT) $(UNITTEST) ./$(OUT)/test_strspl

clean:
	$(RM) -r $(OBJ)
	$(RM) -r $(OUT)

.PHONY: test test_strspl clean all

