#ifndef ___MSTRING_H__
#define ___MSTRING_H__

#include <stdarg.h>

#include "types.h"

int msprintf(char **out, const char *format, ...);

int vmsprintf(char **out, const char *format, va_list args);

char *mstrcat(char **dest, const char *src);

bool startswith(const char *str, const char *start);

bool endswith(const char *str, const char *end);

int strspl(string_array_t *out, const char *str, const char *delim);

int strjoin(char **out, string_array_t arr, const char *first,
            const char *delim, const char *last);

#endif //___MSTRING_H__
