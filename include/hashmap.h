#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include "types.h"

typedef struct hashmap hashmap_t;

hashmap_t *hashmap_new(hashfunction_t hasher);

hashmap_t *hashmap_new_prealloc(hashfunction_t hasher, size_t initial_cap);

int hashmap_put(hashmap_t *map, void *key, size_t keysize, void *value);

void *hashmap_get(const hashmap_t *map, const void *key, size_t keysize) __attribute__((pure));

size_t hashmap_size(const hashmap_t *map) __attribute__((pure, const));

bool hashmap_contains_key(const hashmap_t *map, const void *key, size_t keysize) __attribute__((pure, const));

int hashmap_foreach(const hashmap_t *map, void (*cb)(void *key, size_t keysize, void *value, void *pipe), void *pipe);

int hashmap_clear(hashmap_t *map);

void *hashmap_remove(hashmap_t *map, void *key, size_t keysize);

void hashmap_destroy(hashmap_t *map);

#endif //__HASHMAP_H__

