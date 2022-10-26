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
CFLAGS=-pedantic -pipe -Wall -Werror -g -fPIC

SCRIPTS=scripts
UNITTEST=$(SCRIPTS)/unittest

TEST_DIR=test

OBJCPY=objcopy

FORMATTER=clang-format
FORMATTER_OPTIONS=-i

