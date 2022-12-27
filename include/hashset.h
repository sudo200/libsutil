#ifndef ___HASHSET_H__
#define ___HASHSET_H__

#include "types.h"

typedef struct hashset hashset;

hashset *hashset_new(hashfunction_t func);

hashset *hashset_new_prealloc(size_t initial_cap, hashfunction_t func);

size_t hashset_size(const hashset *set);

int hashset_add(hashset *set, void *item, size_t size);

int hashset_clear(hashset *set);

void *hashset_remove(hashset *set, void *item, size_t size);

int hashset_foreach(hashset *set, void (*cb)(void *item, size_t size, void *pipe), void *pipe);

bool hashset_contains(hashset *set, const void *item, size_t size);

void hashset_destroy(hashset *set);

#endif //___HASHSET_H__
