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
include $(TEST_DIR)/tests.mk


$(OUT)/lib$(LIBNAME).so: $(OUT) $(OBJ)/strspl.o $(OBJ)/file.o $(OBJ)/mstring.o $(OBJ)/dmem.o $(OBJ)/arraylist.o
	$(CC) -shared -o$(OUT)/lib$(LIBNAME).so $(OBJ)/*.o
	chmod -x $(OUT)/lib$(LIBNAME).so	
	$(OBJCPY) --only-keep-debug $(OUT)/lib$(LIBNAME).so $(OUT)/lib$(LIBNAME).so.dbg
	chmod -x $(OUT)/lib$(LIBNAME).so.dbg
	$(OBJCPY) --strip-unneeded $(OUT)/lib$(LIBNAME).so
	$(OBJCPY) --add-gnu-debuglink=$(OUT)/lib$(LIBNAME).so.dbg $(OUT)/lib$(LIBNAME).so

$(OBJ)/dmem.o: $(OBJ) $(SRC)/dmem.c $(INCLUDE)/dmem.h $(INCLUDE)/types.h
	$(CC) -c -I$(INCLUDE) -o$(OBJ)/dmem.o $(SRC)/dmem.c $(FLAGS)

$(OBJ)/strspl.o: $(OBJ) $(SRC)/strspl.c $(INCLUDE)/strspl.h $(INCLUDE)/dmem.h $(INCLUDE)/types.h
	$(CC) -c -I$(INCLUDE) -o$(OBJ)/strspl.o $(SRC)/strspl.c $(CFLAGS)

$(OBJ)/file.o: $(OBJ) $(SRC)/file.c $(INCLUDE)/file.h $(INCLUDE)/dmem.h $(INCLUDE)/types.h
	$(CC) -c -I$(INCLUDE) -o$(OBJ)/file.o $(SRC)/file.c $(CFLAGS)

$(OBJ)/mstring.o: $(OBJ) $(SRC)/mstring.c $(INCLUDE)/mstring.h $(INCLUDE)/dmem.h $(INCLUDE)/types.h
	$(CC) -c -I$(INCLUDE) -o$(OBJ)/mstring.o $(SRC)/mstring.c $(CFLAGS)

$(OBJ)/arraylist.o: $(OBJ) $(SRC)/arraylist.c $(INCLUDE)/arraylist.h $(INCLUDE)/dmem.h $(INCLUDE)/types.h
	$(CC) -c -I$(INCLUDE) -o$(OBJ)/arraylist.o $(SRC)/arraylist.c $(CFLAGS)

$(OUT):
	mkdir -p $(OUT)

$(OBJ):
	mkdir -p $(OBJ)

all: $(OUT)/lib$(LIBNAME).so

build: all

clean:
	$(RM) -r $(OBJ)
	$(RM) -r $(OUT)

compile-config: clean
	bear -- $(MAKE) build

.PHONY: clean build all

