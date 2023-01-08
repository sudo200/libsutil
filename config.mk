##################
#    libsutil    #
#                #
#  sudo200 and   #
#  contributors  #
#                #
#	 Build config  #
#	     file      #
##################

DYN_LD ?= '"$(shell echo | $(CC) -xc - -v 2>&1 | grep -- '-dynamic-linker' | tr '[:space:]' '\n' | grep -A1 -P -- '^-dynamic-linker$$' | tr '\n' ' ' | cut -d ' ' -f '2-' | sed 's/[[:space:]]*$$//')"'

INCLUDE := include
SRC := src
OUT := out
OBJ := obj
LIBNAME := sutil
CFLAGS := -pedantic -pipe -Wall -Werror -g -fPIC -D__LD=$(DYN_LD)

SCRIPTS := scripts
UNITTEST := $(SCRIPTS)/unittest

TEST_DIR := test

LIBINSTALLDIR ?= /usr/local/lib
LIBINCLUDEINSTALLDIR ?= /usr/local/include

OBJCPY ?= objcopy
CPY ?= cp

FORMATTER ?= clang-format
FORMATTER_OPTIONS ?= -i

DOCGEN ?= clang-doc
DOCGEN_OPTIONS ?= --doxygen --format=md --output=docs --p=.

