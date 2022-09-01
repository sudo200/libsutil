#include <string.h>

#include "strspl.h"

int strspl(string_array_t *out, const char * string, const char delim)
{
  out->len = 1;
  if((out->arr = (char **) malloc(out->len * sizeof(*out->arr))) == NULL)
    return -1;

  char * cpy = *out->arr = strdup(string);
  char * next;

  while((next = strchr(cpy, delim)) != NULL)
  {
    *next++ = '\0';
    if((out->arr = (char **) realloc(out->arr, sizeof(*out->arr) * ++out->len)) == NULL)
      return -1;
    out->arr[out->len - 1] = cpy = next;
  }
  return 0;
}

