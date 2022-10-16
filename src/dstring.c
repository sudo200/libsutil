#include <string.h>

#include "dmem.h"
#include "dstring.h"

#define LEN(dstr) (*((size_t *) dstr - 1))


dstring dstring_new(const char *str)
{
  const size_t len = (str == NULL) ? 0UL : strlen(str) + 1;
  str = (str == NULL) ? "" : str;
  return dstring_new_binsave(str, len); 
}

dstring dstring_new_binsave(const void *str, size_t len)
{
  size_t *dstr = (size_t *) ualloc(sizeof(char) * len + sizeof(len));
  if(dstr == NULL)
    return NULL;
  *dstr++ = len;
  if(len > 0)
    memcpy(dstr, str, sizeof(char) * len);
  return (dstring) dstr;
}

size_t dstring_length(dstring dstr)
{
  if(dstr == NULL)
    return 0UL;

  return LEN(dstr) - 1;
}

int dstring_cat(dstring *dstr, const char *str)
{
  if(str == NULL)
    return -1;

  return dstring_cat_binsave(dstr, str, strlen(str) + 1);
}

int dstring_cat_binsave(dstring *dstr, const void *str, size_t len)
{
  if(dstr == NULL || *dstr == NULL || str == NULL)
    return -1;

  const size_t initial_len = LEN(*dstr);
  size_t * initial_ptr = ((size_t *) *dstr - 1);

  initial_ptr = (size_t *) urealloc(initial_ptr, sizeof(size_t) + initial_len + len);

  if(initial_ptr == NULL)
    return -1;

  *initial_ptr++ = initial_len + len - 1;

  memcpy(((char *) initial_ptr) + initial_len - 1, str, len);

  *dstr = (dstring) initial_ptr;

  return 0;
}

int dstring_cmp(dstring dstr, const char *str)
{
  return dstring_cmp_binsave(dstr, str, strlen(str) + 1);
}

int dstring_cmp_binsave(dstring dstr, const void *str, size_t len)
{
  return memcmp(dstr, str, len);
}

void dstring_destroy(dstring *dstr)
{
  if(dstr == NULL || *dstr == NULL)
    return;

  ufree(((size_t *) *dstr) - 1);
}

