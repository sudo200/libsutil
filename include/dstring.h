#ifndef  ___DSTRING_H__
#define  ___DSTRING_H__

#include "types.h"

/**
 * The datatype of a dynamic string.
 *
 * This is compatible with every standard function accepting
 * a constant string (const char *).
 *
 * This string is also binary save, and can therefore
 * be used to store abitrary data.
 */
typedef const char * dstring;

/**
 * Creates a new dynamic string.
 *
 * @param str The initial string, if NULL empty.
 * @return The dynamic string.
 */
dstring dstring_new(const char *str);

/**
 * Creates a new dynamic string with given length.
 */
dstring dstring_new_binsave(const void *str, size_t len);

size_t dstring_length(dstring dstr);

int dstring_cat(dstring *dstr, const char *str);

int dstring_cat_binsave(dstring *dstr, const void *str, size_t len);

int dstring_cmp_dstring(dstring dstr1, dstring dstr2);

int dstring_cmp(dstring dstr, const char *str);

int dstring_cmp_binsave(dstring dstr, const void *str, size_t len);

void dstring_destroy(dstring *dstr);

#endif// ___DSTRING_H__

