#ifndef ___DSTRING_H__
#define ___DSTRING_H__

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
typedef const char *dstring;

/**
 * Creates a new dynamic string.
 *
 * @param str The initial string, if NULL empty.
 * @return The dynamic string.
 */
dstring dstring_new(const char *str);

/**
 * Creates a new dynamic string with given length.
 *
 * @param str The initial string.
 * @param len The length of the initial string.
 * @return The dynamic string.
 */
dstring dstring_new_binsave(const void *str, size_t len);

/**
 * Gets the length of the dynamic string.
 *
 * @param dstr The dynamic string.
 * @return The length of the dynamic string.
 */
size_t dstring_length(dstring dstr);

/**
 * Concats a string onto the dynamic string like strcat().
 *
 * @param dstr The dynamic string to concat onto.
 * @param str The string, which gets concatted.
 * @return 0 if successful, else a negative value.
 */
int dstring_cat(dstring *dstr, const char *str);

/**
 * Concats a string with the given length onto the dynamic string like strcat().
 *
 * @param dstr The dynamic string to concat onto.
 * @param str The string, which gets concatted.
 * @param len The lenght of the string.
 * @return 0 if successful, else a negative value.
 */
int dstring_cat_binsave(dstring *dstr, const void *str, size_t len);

/**
 * Compares a dynamic string and another string.
 *
 * @param dstr,str The strings to compare.
 * @return A number like strcmp() or memcmp().
 */
int dstring_cmp(dstring dstr, const char *str);

/**
 * Compares a dynamic string and one with given length.
 *
 * @param dstr,str The strings to compare.
 * @return A number like strcmp() or memcmp().
 */
int dstring_cmp_binsave(dstring dstr, const void *str, size_t len);

/**
 * Destroys the dynamic string.
 *
 * @param dstr The dynamic string to destroy.
 */
void dstring_destroy(dstring *dstr);

#endif // ___DSTRING_H__
