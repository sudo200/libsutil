#ifndef ___MSTRING_H__
#define ___MSTRING_H__

#include <stdarg.h>

#include "types.h"

int msprintf(char **out, const char *format, ...);

int vmsprintf(char **out, const char *format, va_list args);

char * mstrcat(char **dest, const char *src);

#endif//___MSTRING_H__

