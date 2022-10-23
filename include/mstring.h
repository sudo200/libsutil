#ifndef ___MSTRING_H__
#define ___MSTRING_H__

#include <stdarg.h>

#include "types.h"

int msprintf(char **out, const char *format, ...);

int vmsprintf(char **out, const char *format, va_list args);

char *mstrcat(char **dest, const char *src);

bool startswith(const char *str, const char *start);

bool endswith(const char *str, const char *end);

#endif //___MSTRING_H__
