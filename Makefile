###################
#    libsutils    #
#                 #
#   sudo200 and   #
#  contributors   #
#                 #
#  Main makefile  #
#                 #
###################

include config.mk


all: $(OUT)/lib$(LIBNAME).so
	$(CPY) -r $(INCLUDE) $(OUT)/$(LIBNAME)

$(OUT)/lib$(LIBNAME).so: $(OUT) \
	$(OBJ)/file.o \
	$(OBJ)/mstring.o \
	$(OBJ)/dmem.o \
	$(OBJ)/arraylist.o \
	$(OBJ)/linkedlist.o \
	$(OBJ)/queue.o \
	$(OBJ)/util.o \
	$(OBJ)/argparser.o \
	$(OBJ)/logger.o \
	$(OBJ)/stack.o \
	$(OBJ)/globals.o \
	$(OBJ)/hash.o \
	$(OBJ)/hashset.o \
	$(OBJ)/buffer.o \
	$(OBJ)/hashmap.o \
	
	$(CC) -shared -o$(OUT)/lib$(LIBNAME).so $(wildcard $(OBJ)/*.o) $(LDFLAGS)
	#chmod -x $(OUT)/lib$(LIBNAME).so	
	$(OBJCPY) --only-keep-debug $(OUT)/lib$(LIBNAME).so $(OUT)/lib$(LIBNAME).so.dbg
	chmod -x $(OUT)/lib$(LIBNAME).so.dbg
	$(OBJCPY) --strip-unneeded $(OUT)/lib$(LIBNAME).so
	$(OBJCPY) --add-gnu-debuglink=$(OUT)/lib$(LIBNAME).so.dbg $(OUT)/lib$(LIBNAME).so

$(OBJ)/%.o: $(OBJ) $(SRC)/%.c
	$(CC) -c -o '$@' -I'$(INCLUDE)' '$(SRC)/$(patsubst $(OBJ)/%.o,%,$@).c' $(CFLAGS)


$(OUT):
	mkdir -p $(OUT)

$(OBJ):
	mkdir -p $(OBJ)


build: all

install: all
	$(CPY) $(OUT)/lib$(LIBNAME).so $(LIBINSTALLDIR)
	[ -d '$(LIBINCLUDEINSTALLDIR)/$(LIBNAME)' ] || $(RM) -r $(LIBINCLUDEINSTALLDIR)/$(LIBNAME)
	$(CPY) -r $(OUT)/$(LIBNAME) $(LIBINCLUDEINSTALLDIR)

uninstall:
	$(RM) -r $(LIBINCLUDEINSTALLDIR)/$(LIBNAME)
	$(RM) $(LIBINSTALLDIR)/lib$(LIBNAME).so

clean:
	$(RM) -r $(OBJ)
	$(RM) -r $(OUT)

compiledb: clean
	$(RM) compile_commands.json
	bear -- $(MAKE) test

format:
	$(FORMATTER) $(FORMATTER_OPTIONS) $(wildcard $(INCLUDE)/*.h) $(wildcard $(SRC)/*.c) $(wildcard $(TEST_DIR)/*.c)

docs:
	$(DOCGEN) $(DOCGEN_OPTIONS) $(wildcard $(INCLUDE)/*.h) $(wildcard $(SRC)/*.c)

include $(TEST_DIR)/tests.mk

.PHONY: clean build all compile-config format install uninstall docs
