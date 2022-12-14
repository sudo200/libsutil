#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dmem.h"
#include "mstring.h"

#define LETTER_CASE_OFFSET 32U

int msprintf(char **out, const char *format, ...) {
  va_list args;
  va_start(args, format);
  const int r = vmsprintf(out, format, args);
  va_end(args);
  return r;
}

int vmsprintf(char **out, const char *format, va_list args) {
  va_list args_cpy;
  va_copy(args_cpy, args);

  if (out == NULL)
    return -1;

  const int size = vsnprintf(NULL, 0, format, args) + 1;
  if (size <= 0)
    return -1;

  if ((*out = (char *)ualloc(size)) == NULL)
    return -1;

  const int r = vsnprintf(*out, size, format, args_cpy);
  va_end(args_cpy);
  return r;
}

char *mstrcat(char **dest, const char *src) {
  const size_t len = strlen(*dest) + strlen(src) + 1;
  if ((*dest = (char *)urealloc(*dest, len)) == NULL)
    return NULL;
  return strcat(*dest, src);
}

bool startswith(const char *str, const char *start) {
  size_t start_len = strlen(start);

  if (start_len > strlen(str))
    return false;

  return memcmp(str, start, start_len) == 0;
}

bool endswith(const char *str, const char *end) {
  size_t str_len = strlen(str), end_len = strlen(end);

  if (end_len > str_len)
    return false;

  return memcmp(str + str_len - end_len, end, end_len) == 0;
}

int strspl(string_array_t *out, const char *str, const char *delim) {
  const size_t delim_len = strlen(delim);
  char *substr;

  out->arr = (char **)ualloc(sizeof(char *));
  msprintf(out->arr, "%s", str);
  out->len = 1;

  while ((substr = strstr(out->arr[out->len - 1], delim)) != NULL) {
    *substr = '\0';
    substr += delim_len;
    if ((out->arr = (char **)urealloc(out->arr,
                                      sizeof(char *) * (++out->len))) == NULL)
      return -1;
    out->arr[out->len - 1] = substr;
  }

  return 0;
}

int strjoin(char **out, string_array_t arr, const char *first,
            const char *delim, const char *last) {
  if ((*out = ualloc(sizeof(char))) == NULL)
    return -1;
  **out = '\0';

  if (first != NULL && mstrcat(out, first) == NULL)
    return -1;

  size_t i;
  for (i = 0; i < (arr.len - 1); i++) {
    if (mstrcat(out, arr.arr[i]) == NULL)
      return -1;

    if (delim != NULL && mstrcat(out, delim) == NULL)
      return -1;
  }
  if (mstrcat(out, arr.arr[i]) == NULL)
    return -1;

  if (last != NULL && mstrcat(out, last) == NULL)
    return -1;

  return 0;
}

char *strreplace(char **str, const char *search, const char *replace) {
  if (str == NULL || search == NULL || replace == NULL)
    return NULL;

  if (strlen(*str) == 0UL)
    return *str;

  string_array_t split;
  if (strspl(&split, *str, search) < 0)
    return NULL;

  char *new_str = (char *)ualloc(sizeof(*new_str));
  *new_str = '\0';

  for (size_t i = 0UL; i < split.len; i++) {
    if (mstrcat(&new_str, split.arr[i]) == NULL)
      return NULL;
    if (mstrcat(&new_str, replace) == NULL)
      return NULL;
  }
  new_str[strlen(new_str) - 1] = '\0';
  ufree(*split.arr);
  ufree(split.arr);
  ufree(*str);

  return *str = new_str;
}

char *strupp(char *str) {
  if (str == NULL)
    return NULL;

  for (char *s = str; *s != '\0'; s++)
    if (*s <= 'z' && *s >= 'a')
      *s -= LETTER_CASE_OFFSET;

  return str;
}

char *strlow(char *str) {
  if (str == NULL)
    return NULL;

  for (char *s = str; *s != '\0'; s++)
    if (*s <= 'Z' && *s >= 'A')
      *s += LETTER_CASE_OFFSET;

  return str;
}

char *strnstr(const char *haystack, const char *needle, size_t n) {
  size_t needle_len = strlen(needle);
  if (needle_len == 0)
    return (char *)haystack;

  for (size_t i = 0; i < n; i++) {
    if (i + needle_len > n)
      return NULL;
    if (strncmp(haystack + i, needle, needle_len) == 0)
      return (char *)(haystack + i);
  }

  return NULL;
}
