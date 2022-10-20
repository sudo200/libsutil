#ifndef ___FILE_H__
#define ___FILE_H__

#include "types.h"
#include <stdio.h>

int fpeek(FILE *stream);

char *fpeeks(FILE *stream, size_t n);

size_t fsize(FILE *stream);

#endif //___FILE_H__
