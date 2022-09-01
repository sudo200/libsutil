##################
#    libsutil    #
#                #
#  sudo200 and   #
#  contributors  #
#                #
#	 Build config  #
#	     file      #
##################

INCLUDE=include
SRC=src
OUT=out
OBJ=obj
LIBNAME=sutil
CFLAGS=-pedantic -Wall -g -fPIC

SCRIPTS=scripts
UNITTEST=$(SCRIPTS)/unittest

TEST_DIR=test
TEST_STRSPL=$(TEST_DIR)/strspl_test.c

OBJCPY=objcopy

