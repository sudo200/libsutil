#ifndef ___FILE_H__
#define ___FILE_H__

#include <stdio.h>
#include "types.h"

int fpeek(FILE *stream);

char * fpeeks(FILE *stream, size_t n);

size_t fsize(FILE *stream);

#endif//___FILE_H__

