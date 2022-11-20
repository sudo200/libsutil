#ifndef ___QUEUE_H__
#define ___QUEUE_H__

#include "types.h"

typedef struct queue queue;

/**
 * Creates a new queue, which can hold a maximum of max_len items.
 * Insert operations will return -2, if capacity is exhausted.
 *
 * @return A new queue with max_len capacity.
 */
queue *queue_new_capped(size_t max_len);

/**
 * Creates a new queue, which can theoretically grow to infinity.
 *
 * @return A new uncapped queue.
 */
queue *queue_new_uncapped(void);

/**
 * Adds an element to the queue.
 *
 * @param queue The queue to operate on.
 * @param item  The item to add.
 */
int queue_add(queue *queue, void *item);

/**
 * Adds an array of elements to the queue.
 *
 * @param queue The queue to operate on.
 * @param items The array to add.
 * @param nitems  The length of `items`.
 * @param reverse If true, items get added in reverse order.
 */
int queue_addall(queue *queue, void **items, size_t nitems, bool reverse);

/**
 * Get the next element from the queue without removing it.
 *
 * @param queue The queue to operate on.
 * @return The next element, or NULL if empty.
 */
void *queue_peek(queue *queue);

/**
 * Get the next element from the queue and removes it.
 *
 * @param queue The queue to operate on.
 * @return The next element, or NULL if empty.
 */
void *queue_poll(queue *queue);

/**
 * Get the length of the queue.
 *
 * @param queue The queue to operate on.
 * @return The length of the queue.
 */
size_t queue_length(queue *queue);

/**
 * Destroys the queue.
 * IMPORTANT: Stored elements are not deallocated.
 *
 * @param queue The queue to destroy.
 */
void queue_destroy(queue *queue);

#endif //___QUEUE_H__
