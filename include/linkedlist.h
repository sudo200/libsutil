#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "types.h"

typedef struct linkedlist linkedlist;

/**
 * Creates a new linked list.
 *
 * @return The new linked list, or NULL on error.
 */
linkedlist *linkedlist_new(void);

/**
 * Returns the length of the linked list.
 *
 * @param list The list from to get length from.
 * @return Length of the list
 */
size_t linkedlist_length(linkedlist *list) __attribute__((const, pure));

/**
 * Adds an element to the linked list.
 *
 * @param list The list to add the item to.
 * @param element The element to add.
 * @return 0 on success, a negative value on error.
 */
int linkedlist_add(linkedlist *list, void *element);

/**
 * Adds an array of elements to the linked list.
 *
 * @param list The list to add item to.
 * @param elements The array to add.
 * @param nitems The length of the array.
 * @return 0 on success, a negative value on error.
 */
int linkedlist_addall(linkedlist *list, void **elements, size_t nitems);

/**
 * Inserts an element at index to the linked list.
 *
 * @param list The list to insert the item into.
 * @param element The element to insert.
 * @param index The index at which to insert the element.
 * @return 0 on success, a negative value on error.
 */
int linkedlist_insert(linkedlist *list, void *element, size_t index);

/**
 * Inserts an array of elements at index to the linked list.
 *
 * @param list The list to insert the items into.
 * @param elements The array to insert.
 * @param nitems The length of the array.
 * @param index The index at which to insert the array.
 * @return 0 on success, a negative value on error.
 */
int linkedlist_insertall(linkedlist *list, void **elements, size_t nitems,
                         size_t index);

/**
 * Get the element at specified index.
 *
 * @param list The list to get the item from.
 * @param index The index at which to get the item from.
 * @return The item, or NULL on error.
 */
void *linkedlist_get(linkedlist *list, size_t index) __attribute__((pure));

/**
 * Removes an element at index, and returns it.
 *
 * @param list The item from which to remove the item.
 * @param index The index at which to remove the item.
 * @return The removed element, or NULL on error.
 */
void *linkedlist_remove(linkedlist *list, size_t index);

/**
 * Executes a function for each element in the list.
 *
 * @param list The list to iterate over.
 * @param cb The function to execute for each element in the list.
 * @param pipe A pointer passed through to cb.
 * @return 0 on success, a negative value on error.
 */
int linkedlist_foreach(linkedlist *list, void (*cb)(void *item, void *pipe),
                       void *pipe);

/**
 * Returns an array with a copy of the list's elements.
 *
 * @param list The list to convert into an array.
 * @return The generated array, or NULL on error.
 */
void **linkedlist_to_array(linkedlist *list);

/**
 * Clears the linked list.
 *
 * @param list The list to clear.
 * @return 0 on success, a negative value on error.
 */
int linkedlist_clear(linkedlist *list);

/**
 *  Destroys the linked list.
 *
 *  IMPORTANT: Stored elements are not deallocated!
 *
 *  @param list The list to destroy.
 */
void linkedlist_destroy(linkedlist *list);

#endif // LINKEDLIST_H
