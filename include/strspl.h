#ifndef ___STRSPL_H__
#define ___STRSPL_H__

#include <stdlib.h>

typedef struct
{
  char ** arr;
  size_t len;
}
string_array_t;

int strspl(string_array_t *out, const char * string, const char delim);

#endif//___STRSPL_H__

