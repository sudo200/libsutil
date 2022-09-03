#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mstring.h"

int msprintf(char **out, const char *format, ...)
{
  va_list args;
  va_start(args, format);
  const int r = vmsprintf(out, format, args);
  va_end(args);
  return r;
}

int vmsprintf(char **out, const char *format, va_list args)
{
  va_list args_cpy;
  va_copy(args_cpy, args);

  if(out == NULL)
    return -1;

  const int size = vsnprintf(NULL, 0, format, args) + 1;
  if(size <= 0)
    return -1;

  if((*out = (char *) malloc(size)) == NULL)
    return -1;

  const int r = vsnprintf(*out, size, format, args_cpy);
  va_end(args_cpy);
  return r;
}

char * mstrcat(char **dest, const char *src)
{
  const size_t len = strlen(*dest) + strlen(src) + 1;
  if((*dest = (char *) realloc(*dest, len)) == NULL)
    return NULL;
  return strcat(*dest, src);
}

