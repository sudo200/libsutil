#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "types.h"

typedef struct linkedlist linkedlist;

/**
 * Creates a new linked list.
 */
linkedlist *linkedlist_new(void);

/**
 * Returns the length of the linked list.
 */
size_t linkedlist_length(linkedlist *list);

/**
 * Adds an element to the linked list.
 */
int linkedlist_add(linkedlist *list, void *element);

/**
 * Adds an array of elements to the linked list.
 */
int linkedlist_addall(linkedlist *list, void **elements, size_t nitems);

/**
 * Inserts an element at index to the linked list.
 */
int linkedlist_insert(linkedlist *list, void *element, size_t index);

/**
 * Inserts an array of elements at index to the linked list.
 */
int linkedlist_insertall(linkedlist *list, void **elements, size_t nitems,
                         size_t index);

/**
 * Get the element at specified index.
 *
 * If index is out of bounds, return NULL.
 */
void *linkedlist_get(linkedlist *list, size_t index);

/**
 * Removes an element at index, and returns it.
 */
void *linkedlist_remove(linkedlist *list, size_t index);

/**
 * Executes a function for each element in the list.
 */
int linkedlist_foreach(linkedlist *list, void (*func)(void *item, void *pipe), void *pipe);

/**
 * Returns an array with a copy of the list's elements.
 */
void **linkedlist_to_array(linkedlist *list);

/**
 * Clears the linked list.
 */
int linkedlist_clear(linkedlist *list);

/**
 *  Destroys the linked list.
 *
 *  IMPORTANT: Stored elements are not deallocated!
 */
void linkedlist_destroy(linkedlist *list);

#endif // LINKEDLIST_H
