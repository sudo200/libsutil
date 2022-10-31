#ifndef ___ARRAYLIST_H__
#define ___ARRAYLIST_H__

#include "types.h"

typedef struct arraylist arraylist;

/**
 * Creates a new arraylist.
 *
 * @return The new arraylist, or NULL if an error occured.
 */
arraylist *arraylist_new();

/**
 * Adds the given element at the end of the arraylist.
 *
 * @param list The arraylist to operate on.
 * @param item The item to add.
 * @return 0 if successful, else a negative value.
 */
int arraylist_add(arraylist *list, void *item);

/**
 * Adds the given array to the end of the arraylist.
 *
 * @param list The arraylist to operate on.
 * @param items The array of items to add.
 * @param nitems The length of the array.
 * @return 0 if successful, else a negative value.
 */
int arraylist_addall(arraylist *list, void **items, size_t nitems);

/**
 * Inserts the given element at index into the arraylist.
 *
 * @param list The list to operate on.
 * @param item The item to insert.
 * @param index The index to insert at.
 * @return 0 if successful, else a negative value.
 */
int arraylist_insert(arraylist *list, void *item, size_t index);

/**
 * Inserts the given array at index into the arraylist.
 *
 * @param list The list to operate on.
 * @param items The array of items to insert.
 * @param nitems The length of the array.
 * @param index The index to insert at.
 * @return 0 if successful, else a negative value.
 */
int arraylist_insertall(arraylist *list, void **items, size_t nitems,
                        size_t index);

/**
 * Gets the element at the given index.
 *
 * @param list The arraylist to operate on.
 * @param index The index from which to get the value.
 * @return The element at index, or NULL if an error occured.
 */
void *arraylist_get(arraylist *list, size_t index);

/**
 * Gets the length (element count) of the arraylist.
 *
 * @param list The arraylist to operate on.
 * @return The length.
 */
size_t arraylist_length(arraylist *list);

/**
 * Removes the element at given index from the arraylist and returns it.
 *
 * @param list The arraylist to operate on.
 * @param index The index at which to remove the element.
 * @return The element at index, or NULL if an error occured.
 */
void *arraylist_remove(arraylist *list, size_t index);

/**
 * Calls cb with every element in the given arraylist.
 *
 * @param list The arraylist to operate on.
 * @param cb The function to execute for each element.
 * @param pipe A pointer to a variable to be mutated by the callback.
 * @return 0 if successful, else a negative value.
 */
int arraylist_foreach(arraylist *list, void (*cb)(void *item, void *pipe),
                      void *pipe);

/**
 * Returns an array with a copy of to lists elements.
 *
 * @param list The list to convert to an array.
 * @return The generated array, or NULL on error.
 */
void **arraylist_to_array(arraylist *list);

/**
 * Empties the given arraylist.
 * Stored elements are not deallocated.
 *
 * @param list The arraylist to operate on.
 * @return 0 if successful, else a negative value.
 */
int arraylist_clear(arraylist *list);

/**
 * Destroyes the given arraylist.
 *
 * IMPORTANT: Stored elements are not deallocated.
 *
 * @param list The arraylist to operate on.
 */
void arraylist_destroy(arraylist *list);

#endif //___ARRAYLIST_H__
