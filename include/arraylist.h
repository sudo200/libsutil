#ifndef ___ARRAYLIST_H__
#define ___ARRAYLIST_H__

#include "types.h"

typedef struct arraylist_t arraylist_t;

arraylist_t * arraylist_new();

arraylist_t * arraylist_new_prealloc(size_t init_size);

int arraylist_add(arraylist_t *list, void *item);

int arraylist_addall(arraylist_t *list, void **items, size_t nitems);

int arraylist_insert(arraylist_t *list, void *item, size_t index);

int arraylist_insertall(arraylist_t *list, void **items, size_t nitems, size_t index);

void * arraylist_get(arraylist_t *list, size_t index);

size_t arraylist_length(arraylist_t *list);

void * arraylist_remove(arraylist_t *list, size_t index);

int arraylist_foreach(arraylist_t *list, void (*cb)(void *));

int arraylist_clear(arraylist_t *list);

void arraylist_destroy(arraylist_t *list);

#endif//___ARRAYLIST_H__

