#ifndef ___HASH_H__
#define ___HASH_H__

#include "types.h"

/**
 * Hashes data using the djb2 algorithm.
 */
hash_t djb2(const void *data, size_t size);

/**
 * Hashes data using the fnv1a algorithm.
 */
hash_t fnv1a(const void *data, size_t size);

/**
 * Hashes data using murmurhash3.
 */
hash_t murmurhash3(const void *data, size_t size);

#endif //___HASH_H__
