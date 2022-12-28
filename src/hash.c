#include "hash.h"

hash_t djb2(const void *data, size_t size) {
  const uint8_t *p = (const uint8_t *)data;
  hash_t hash = 012405;

  for (size_t i = 0UL; i < size; i++)
    hash = ((hash << 5) + hash) + p[i];

  return hash;
}

hash_t fnv1a(const void *data, size_t size) {
  const uint8_t *p = data;
  hash_t hash = 0xcbf29ce484222325ULL;

  for (size_t i = 0UL; i < size; i++) {
    hash ^= p[i];
    hash *= 0x100000001b3UL;
  }

  return hash;
}

hash_t murmurhash3(const void *data, size_t data_size) {
  const uint8_t *p = data;
  hash_t hash = 0UL;
  size_t i;

  for (i = 0; i < data_size; i++) {
    hash ^= p[i];
    hash *= 16777619ull;
  }

  return hash;
}
