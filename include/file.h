#ifndef ___FILE_H__
#define ___FILE_H__

#include "types.h"
#include <stdio.h>

/**
 * Get an character from the specified stream without removing it from the stream.
 *
 * @param stream The file stream to peek the character from.
 * @return The peeked character, or a negative value if an error occured.
 */
int fpeek(FILE *stream);

/**
 * Get a string with n characters from the specified stream without removing them from the stream.
 *
 * @param stream The file stream to peek the string from.
 * @param n The length of the string to peek.
 * @return The peeked string, or NULL if an error occured.
 */
char *fpeeks(FILE *stream, size_t n);

/**
 * Get the size of the stream in bytes.
 *
 * IMPORTANT: Only works with streams, which support seeking (i.e. Files).
 *
 * @param stream The file stream to get the size from.
 * @return The size in bytes of the stream.
 */
size_t fsize(FILE *stream);

#endif //___FILE_H__
