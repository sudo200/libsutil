#ifndef ___ARRAYLIST_H__
#define ___ARRAYLIST_H__

#include "types.h"

/**
 * Reverses the order of elements in memory.
 *
 * @param arr The memory area to reverse.
 * @param nitems The amount of items in the area.
 * @param size The size in bytes of an item.
 * @return a pointer to arr, or NULL if an error occured.
 */
void *memrev(void *arr, size_t nitems, size_t size);

#endif //___ARRAYLIST_H__
