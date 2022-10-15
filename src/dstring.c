#include <string.h>

#include "dmem.h"
#include "dstring.h"

// Private functions

struct __dstring_read_ret_val_struct
{
  size_t *len;
  void *str;
} __dstring_deconstruct(dstring dstr)
{
  if(dstr == NULL)
    return (struct __dstring_read_ret_val_struct) {
    .len = NULL,
    .str = NULL,
  };

  size_t *len = ((size_t *) dstr) - 1;
  return (struct __dstring_read_ret_val_struct) {
    .len = len,
    .str = (void *) dstr,
  };
}

// Public functions

dstring dstring_new(const char *str)
{
  const size_t len = (str == NULL) ? 0UL : strlen(str) + 1;
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

  return *__dstring_deconstruct(dstr).len;
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

  struct __dstring_read_ret_val_struct dcomp = __dstring_deconstruct(*dstr);
  dcomp.len = (size_t *) urealloc(dcomp.len, sizeof(char) * (*dcomp.len + len) + sizeof(*dcomp.len));

  if(dcomp.len == NULL)
    return -1;

  memcpy(((char *) dcomp.str) + *dcomp.len, str, len);
  return 0;
}

int dstring_cmp_dstring(dstring dstr1, dstring dstr2)
{
  return dstring_cmp_binsave(dstr1, dstr2, dstring_length(dstr2));
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

  ufree(__dstring_deconstruct(*dstr).len);
}

