#ifndef ___HASHSET_H__
#define ___HASHSET_H__

#include "types.h"

typedef struct hashset hashset_t;

hashset_t *hashset_new(hashfunction_t func);

hashset_t *hashset_new_prealloc(size_t initial_cap, hashfunction_t func);

size_t hashset_size(const hashset_t *set);

int hashset_add(hashset_t *set, void *item, size_t size);

int hashset_clear(hashset_t *set);

bool hashset_remove(hashset_t *set, void *item, size_t size);

int hashset_foreach(const hashset_t *set,
                    void (*cb)(void *item, size_t size, void *pipe),
                    void *pipe);

bool hashset_contains(const hashset_t *set, const void *item, size_t size);

void hashset_destroy(hashset_t *set);

#endif //___HASHSET_H__
