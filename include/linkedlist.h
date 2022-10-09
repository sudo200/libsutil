#ifndef  LINKEDLIST_H
#define  LINKEDLIST_H

#include "types.h"

typedef struct linkedlist linkedlist;

/**
 * Creates a new linked list.
 */
linkedlist * linkedlist_new(void);

/**
 * Returns the length of the linked list.
 */
size_t linkedlist_length(linkedlist * list);

/**
 * Add an element to the linked list.
 */
linkedlist * linkedlist_add(linkedlist * list, void * element);

/**
 * Get the element at specified index.
 *
 * If index is out of bounds, return NULL.
 */
void * linkedlist_get(linkedlist * list, size_t index);

/**
 * Removes an element at index, and returns it.
 */
void * linkedlist_remove(linkedlist * list, size_t index);

/**
 * Executes a function for each element in the list.
 */
linkedlist * linkedlist_foreach(linkedlist * list, void (*func)(void *));

/**
 *  Destroys the linked list.
 *
 *  Stored elements are not deallocated!
 */
void linkedlist_destroy(linkedlist * list);

#endif// LINKEDLIST_H

