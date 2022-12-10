#ifndef ___MSTRING_H__
#define ___MSTRING_H__

#include <stdarg.h>

#include "types.h"

/**
 * Like sprintf, but allocates a buffer big enough
 * to hold the finished string.
 *
 * @param out The pointer to the output string.
 * @param format The format string.
 * @param ... Arguments, as specified by format.
 * @return The amount of bytes written, or a negative value on error.
 */
int msprintf(char **out, const char *format, ...);

/**
 * Like msprintf, but gets the varargs from a va_list.
 *
 * @param out The pointer to the output string.
 * @param format The format string.
 * @param args The Arguments, as specified by format.
 * @return The amount of bytes written, or a negative value on error.
 */
int vmsprintf(char **out, const char *format, va_list args);

/**
 * Like strcat, but automatically reallocates the dest-buffer
 * to hold the concatenated string.
 *
 * IMPORTANT: dest has to be dynamically allocates using
 * another library function or ualloc/urealloc.
 *
 * @param dest The pointer to the string onto which src should be concatenated.
 * @param src The string to be concatenated onto dest.
 * @return dest, or NULL on error.
 */
char *mstrcat(char **dest, const char *src);

/**
 * Returns true if str starts with start, false otherwise.
 *
 * @param str The string the check the start of.
 * @param start The string with which str should start.
 * @return true if str starts with start, false otherwise.
 */
bool startswith(const char *str, const char *start);

/**
 * Returns true if str ends with end, false otherwise.
 *
 * @param str The string to check the end of.
 * @param end The string with which str should end.
 * @return true if str ends with end, false otherwise.
 */
bool endswith(const char *str, const char *end);

/**
 * Splits the string str on every occurance of delim.
 *
 * @param out The pointer to a string_array_t struct.
 * @param str The string to split.
 * @param delim The delimiter string where a split should occure.
 * @return 0 on success, a negative value otherwise.
 */
int strspl(string_array_t *out, const char *str, const char *delim);

/**
 * Joins a string array to a string.
 *
 * @param out The pointer to the output string.
 * @param arr The string array to join.
 * @param first A string to place at the start of out; can be omitted by passing
 * NULL.
 * @param delim A string to place between joined elements; can be omitted by
 * passing NULL.
 * @param last A string to place at the end of out; can be omitted by passing
 * NULL.
 */
int strjoin(char **out, string_array_t arr, const char *first,
            const char *delim, const char *last);

/**
 * Replaces search by replace for every occurance in str.
 *
 * @param str The string to search and replace in.
 * @param search The string to search for in str.
 * @param replace The string to replace every occurance of search in str with.
 * @return str or NULL on error.
 */
char *strreplace(char **str, const char *search, const char *replace);


/**
 * Converts the string {@args str} to UPPERCASE.
 *
 * @param str The string to convert to uppercase.
 * @return {@args str} or {@value NULL} on error.
 */
char *strupp(char *str);


/**
 * Converts the string {@args str} to lowercase.
 *
 * @param str The string to convert to lowercase.
 * @return {@args str} or {@value NULL} on error.
 */
char *strlow(char *str);

#endif //___MSTRING_H__
